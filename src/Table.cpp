#include "Table.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <map>
#include <utility>

namespace indexvsscan {

Table::Table(const BenchmarkConfig& config) : num_rows(config.num_rows) {
  std::cout << "### Create table: " << config.column_definitions.size() << " colums, " << config.num_rows
  << " random rows ###\n";

  const auto start = std::chrono::steady_clock::now();

  size_t int_count = 0, string_count = 0;
  for (const auto& definition : config.column_definitions) {
    const auto [column_type, value_count, selectivity, value] = definition;

    if (column_type == ColumnType::Int) {
      _make_column(column_type, config.num_rows);
      _fill_int_column(int_count, value_count, selectivity, config.num_rows, value);
      int_count++; //TODO unnecessary
      std::cout << "Created IntColumn " << int_count << "\n";
    }
    else if (column_type == ColumnType::String) {
      _make_column(column_type, string_count);
      _fill_string_column(string_count, value_count, selectivity, config.num_rows, value);
      string_count++;
      std::cout << "Created StringColumn " << string_count << "\n";
    }
  }

  const auto end = std::chrono::steady_clock::now();
  const auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

  std::cout << "Created table in " << duration << " seconds.\n\n";
}

void Table::_make_column(const ColumnType type, const long num_rows) {
  if (type == ColumnType::Int) {
    if (!_int_columns) {
      _int_columns = std::make_shared<std::vector<IntColumn>>();
    }

    auto& columns = *_int_columns;
    columns.emplace_back(IntColumn());
    columns[columns.size() - 1].reserve(num_rows);
  }
  else if (type == ColumnType::String) {
    if (!_string_columns) _string_columns = std::make_shared<std::vector<StringColumn>>();

    if (!_string_dictionaries) {
      _string_dictionaries = std::make_shared<std::vector<StringColumn>>();
      _string_avs = std::make_shared<std::vector<IntColumn>>();
      _string_offsets = std::make_shared<std::vector<IntColumn>>();
      _string_indizes = std::make_shared<std::vector<IntColumn>>();
    }

    if (!_string_trees) {
        _string_trees = std::make_shared<std::vector<StringTree>>();
    }

    auto& columns = *_string_columns;
    columns.emplace_back(StringColumn());
    columns[columns.size() - 1].reserve(num_rows);

    _string_dictionaries->emplace_back(StringColumn());
    _string_avs->emplace_back(IntColumn());
    _string_offsets->emplace_back(IntColumn());
    _string_indizes->emplace_back(IntColumn());
    _string_trees->emplace_back(StringTree());
  }
}

void Table::_fill_int_column(const size_t index, const uint32_t value_count, double selectivity,
        const long num_rows, const uint32_t value) {
  std::mt19937 generator(1337);

  auto num_selected_value = static_cast<long>(selectivity * num_rows);
  std::vector<uint32_t> values;
  uint32_t current_value = 0;

  while(values.size() < value_count) {
      if(current_value !=  value) {
          values.push_back(current_value);
      }
      current_value++;
  }

  for (long i = 0; i < num_rows; i++) {
      if(i < num_selected_value) {
          (*_int_columns)[index].push_back(value);
      } else {
          (*_int_columns)[index].push_back(values.at(i % values.size()));
      }
  }

  std::shuffle((*_int_columns)[index].begin(), (*_int_columns)[index].end(), generator);
}

void Table::_fill_string_column(const size_t index, const uint32_t value_count, const double selectivity,
        const long num_rows, const uint32_t value) {
    std::mt19937 generator(1337);


    auto num_selected_value = static_cast<uint32_t >(selectivity * num_rows);
    std::array<char, 10> select_value = {};
    for(size_t i = 0; i < 10; i++) {
        select_value[i] = i < 6 ? 'A' : static_cast<char>(value);
    }

    std::vector<std::array<char, 10>> values;

    for (char char1 = 65; char1 < 123; char1++) {
        for (char char2 = 65; char2 < 123; char2++) {
            for (char char3 = 65; char3 < 123; char3++) {
                for (char char4 = 65; char4 < 123; char4++) {
                    std::array<char, 10> string = { 'A', 'A', 'A', 'A', 'A', 'A', char1, char2, char3, char4 };
                    if(string != select_value) {
                        values.push_back(string);
                    }
                    if (values.size() >= value_count - 1) {
                        goto fill_column;
                    }
                }
            }
        }
    }

    fill_column:
    for (size_t i = 0; i < num_rows; i++) {
        if(i < num_selected_value) {
            (*_string_columns)[index].push_back(select_value);
        } else {
            (*_string_columns)[index].push_back(values.at(i % values.size()));
        }
    }

    std::shuffle((*_string_columns)[index].begin(), (*_string_columns)[index].end(), generator);

  // Map column values to their positions
  std::map<String, std::vector<uint32_t>> map;

  for (uint32_t i = 0; i< (*_string_columns)[index].size(); i++) {
    String val = (*_string_columns)[index][i];

    if (map.find(val) != map.cend()) {
      map[val].push_back(i);
    } else {
      map[val] = std::vector<uint32_t>{i};
    }
  }

  // Make dictionary, attribute vector, offset and index
  (*_string_avs)[index] = IntColumn(num_rows);

  for (auto it = map.begin(); it != map.end(); ++it) {
    (*_string_dictionaries)[index].push_back(it->first);  // Add val to dictionary
    (*_string_offsets)[index].push_back((*_string_indizes)[index].size());  // Add offset

    for (const auto& val : it->second) {
      (*_string_avs)[index][val] = (*_string_dictionaries)[index].size() - 1;  // Fill dictionary position in attribute vector
      (*_string_indizes)[index].push_back(val);  // Add index
    }
  }
  (*_string_offsets)[index].push_back((*_string_indizes)[index].size());

    // Make Btree
    for(size_t i = 0; i < ((*_string_columns)[index].size()); i++) {
        (*_string_trees)[index].insert(std::make_pair((*_string_columns)[index].at(i), i));
    }

}

}  // namespace indexvsscan
