#include "Table.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <map>
#include <utility>

namespace indexvsscan {

Table::Table(const BenchmarkConfig& config) : num_rows(config.num_rows){ //TODO schneller -> map die vektor speichert
  std::cout << "### Create table: " << config.column_definitions.size() << " colums, " << config.num_rows
  << " random rows ###\n";

  const auto start = std::chrono::steady_clock::now();

  size_t int_count = 0, string_count = 0;
  for (const auto& definition : config.column_definitions) {
    const auto [column_type, value_count, operation_type, selectivity, value] = definition;

    if (column_type == ColumnType::Int) {
      _make_column(column_type, config.num_rows);
      _fill_int_column(int_count, value_count, operation_type, selectivity, config.num_rows, value);
      int_count++; //TODO unnecessary
      std::cout << "Created IntColumn " << int_count << "\n";
    }
    else if (column_type == ColumnType::String) {
      _make_column(column_type, string_count);
      _fill_string_column(string_count, value_count, operation_type, selectivity, config.num_rows, value);
      string_count++;
      std::cout << "Created StringColumn " << string_count << "\n";
    }
  }

  const auto end = std::chrono::steady_clock::now();
  const auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

  std::cout << "Created table in " << duration << " seconds.\n\n";
}

void Table::_make_column(const ColumnType type, const size_t num_rows) {
  if (type == ColumnType::Int) {
    if (!_int_columns) {
      _int_columns = std::make_shared<std::vector<IntColumn>>();
    }

    if (!_int_dictionaries) {
      _int_dictionaries = std::make_shared<std::vector<IntColumn>>();
      _int_avs = std::make_shared<std::vector<IntColumn>>();
      _int_offsets = std::make_shared<std::vector<IntColumn>>();
      _int_indizes = std::make_shared<std::vector<IntColumn>>();
    }

    if (!_int_trees) {
        _int_trees = std::make_shared<std::vector<IntTree>>();
    }

    auto& columns = *_int_columns;
    columns.emplace_back(IntColumn());
    columns[columns.size() - 1].reserve(num_rows);

    _int_dictionaries->emplace_back(IntColumn());
    _int_avs->emplace_back(IntColumn());
    _int_offsets->emplace_back(IntColumn());
    _int_indizes->emplace_back(IntColumn());
    _int_trees->emplace_back(IntTree());
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

void Table::_fill_int_column(const size_t index, const uint32_t value_count, OperationType operation_type,
        double selectivity, const uint32_t num_rows, const uint32_t value) {

  std::mt19937 generator(1337);
  auto num_selected_value = static_cast<uint32_t >(selectivity * num_rows);
  std::vector<uint32_t> values;
  uint32_t current_value = 0;

  switch (operation_type) {
      case OperationType::Equals : {
          while (values.size() < value_count - 1) {
              if (current_value != value) {
                  values.push_back(current_value);
              }
              current_value++;
          }

          for (size_t i = 0; i < num_rows; i++) {
              if (i < num_selected_value) {
                  (*_int_columns)[index].push_back(value);
              } else {
                  (*_int_columns)[index].push_back(values.at(i % values.size()));
              }
          }
          break;
      }

      case OperationType::LessOrEquals : {
          std::vector<uint32_t> greater_values;
          values.push_back(value);
          greater_values.push_back(UINT32_MAX);
          while (values.size() < std::min(value_count - 1, num_selected_value)) {
              if (current_value >= value) {
                  break;
              }
              values.push_back(current_value);
              current_value++;
          }

          current_value = UINT32_MAX;
          while (greater_values.size() + values.size() < value_count) {
              current_value--;
              greater_values.push_back(current_value);
          }

          for (size_t i = 0; i < num_rows; i++) {
              if (i < num_selected_value) {
                  (*_int_columns)[index].push_back(values.at(i % values.size()));
              } else {
                  (*_int_columns)[index].push_back(greater_values.at(i % greater_values.size()));
              }
          }
          break;
      }

      default: {
          std::cout << "Operation type nr. " << static_cast<uint32_t>(operation_type) << " is not supported.\n";
          _Exit(1);
      }
  }

  std::shuffle((*_int_columns)[index].begin(), (*_int_columns)[index].end(), generator);

  // Map column values to their positions
  std::map<uint32_t, std::vector<uint32_t>> map;

  for (uint32_t i = 0; i< (*_int_columns)[index].size(); i++) {
    uint32_t val = (*_int_columns)[index][i];

    if (map.find(val) != map.cend()) {
      map[val].push_back(i);
    } else {
      map[val] = std::vector<uint32_t>{i};
    }
  }

  // Make dictionary, attribute vector, offset and index
  (*_int_avs)[index] = IntColumn(num_rows);

  for (auto it = map.begin(); it != map.end(); ++it) {
    (*_int_dictionaries)[index].push_back(it->first);  // Add val to dictionary
    (*_int_offsets)[index].push_back((*_int_indizes)[index].size());  // Add offset

    for (const auto& val : it->second) {
      (*_int_avs)[index][val] = (*_int_dictionaries)[index].size() - 1;  // Fill dictionary position in attribute vector
      (*_int_indizes)[index].push_back(val);  // Add index
    }
  }
  (*_int_offsets)[index].push_back((*_int_indizes)[index].size());

  // Make Btree
  for(size_t i = 0; i < ((*_int_columns)[index].size()); i++) {
      (*_int_trees)[index].insert(std::make_pair((*_int_columns)[index].at(i), i));
  }


}

void Table::_fill_string_column(const size_t index, const uint32_t value_count, OperationType operation_type,
        const double selectivity, const uint32_t num_rows, const uint32_t value) {
    std::mt19937 generator(1337);


    auto num_selected_value = static_cast<uint32_t >(selectivity * num_rows);
    std::array<char, 10> select_value = {};
    for(size_t i = 0; i < 10; i++) {
        if (i < 6) {
            select_value[i] = 'A';
        } else if (i < 9) {
            select_value[i] = '^';
        } else {
            select_value[i] = static_cast<char>(value);
        }
    }

    std::vector<std::array<char, 10>> values;

    switch (operation_type) {
        case OperationType::Equals : {
            for (char char1 = 65; char1 < 123; char1++) {
                for (char char2 = 65; char2 < 123; char2++) {
                    for (char char3 = 65; char3 < 123; char3++) {
                        for (char char4 = 65; char4 < 123; char4++) {
                            for (char char5 = 65; char5 < 123; char5++) {
                                for (char char6 = 65; char6 < 123; char6++) {
                                    std::array<char, 10> string = {'A', 'A', 'A', 'A', char1, char2, char3,
                                                                   char4, char5, char6};
                                    if (string != select_value) {
                                        values.push_back(string);
                                    }
                                    if (values.size() >= value_count - 1) {
                                        goto fill_column;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            fill_column:
            for (size_t i = 0; i < num_rows; i++) {
                if (i < num_selected_value) {
                    (*_string_columns)[index].push_back(select_value);
                } else {
                    (*_string_columns)[index].push_back(values.at(i % values.size()));
                }
            }
            break;
        }

        case OperationType::LessOrEquals : {
            values.push_back(select_value);
            std::vector<std::array<char, 10>> greater_values;
            std::array<char, 10> max_value = {'A', 'A', 'A', 'A', 'z', 'z', 'z', 'z', 'z', 'z'};
            values.push_back(max_value);
            greater_values.push_back(max_value);
            for (char char1 = 65; char1 < 123; char1++) {
                for (char char2 = 65; char2 < 123; char2++) {
                    for (char char3 = 65; char3 < 123; char3++) {
                        for (char char4 = 65; char4 < 123; char4++) {
                            for (char char5 = 65; char5 < 123; char5++) {
                                for (char char6 = 65; char6 < 123; char6++) {
                                    std::array<char, 10> string = {'A', 'A', 'A', 'A', char1, char2, char3,
                                                                   char4, char5, char6};
                                    if (string > select_value) {
                                        goto make_greater_values;
                                    }
                                    values.push_back(string);
                                    if (values.size() >= std::min(value_count - 1, num_selected_value)) {
                                        goto make_greater_values;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            make_greater_values:

            for (char char1 = 122; char1 > 64; char1--) {
                for (char char2 = 122; char2 > 64; char2--) {
                    for (char char3 = 122; char3 > 64; char3--) {
                        for (char char4 = 122; char4 > 64; char4--) {
                            for (char char5 = 122; char5 > 64; char5--) {
                                for (char char6 = 121; char6 > 64; char6--) {
                                    std::array<char, 10> string = {'A', 'A', 'A', 'A', char1, char2, char3,
                                                                   char4, char5, char6};
                                    greater_values.push_back(string);
                                    if (values.size() + greater_values.size() >= value_count) {
                                        goto fill_leq_column;
                                    }
                                }
                            }
                        }
                    }
                }
            }


            fill_leq_column:
            values.push_back(select_value);
            for (size_t i = 0; i < num_rows; i++) {
                if (i < num_selected_value) {
                    (*_string_columns)[index].push_back(values.at(i % values.size()));
                } else {
                    (*_string_columns)[index].push_back(greater_values.at(i % greater_values.size()));
                }
            }
            break;


        }

        default: {
            std::cout << "Operation type nr. " << static_cast<uint32_t >(operation_type) << " is not implemented\n";
            _Exit(1);
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
