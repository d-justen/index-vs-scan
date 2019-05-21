#include "Table.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>

namespace indexvsscan {

Table::Table(const BenchmarkConfig& config) : num_rows(config.num_rows){
  std::cout << "### Create table: " << config.column_definitions.size() << " colums, " << config.num_rows
  << " random rows ###\n";

  const auto start = std::chrono::steady_clock::now();

  size_t int_count = 0, string_count = 0;
  for (const auto& definition : config.column_definitions) {
    const auto [column_type, value_count, distribution] = definition;

    if (column_type == ColumnType::Int) {
      _make_column(column_type, config.num_rows);
      _fill_int_column(int_count, distribution, value_count, config.num_rows);
      int_count++; //TODO unnecessary
    }
    else if (column_type == ColumnType::String) {
      _make_column(column_type, string_count);
      _fill_string_column(string_count, distribution, value_count, config.num_rows);
      string_count++;
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

    auto& columns = *_int_columns;
    columns.emplace_back(IntColumn());
    columns[columns.size() - 1].reserve(num_rows);

    _int_dictionaries->emplace_back(IntColumn());
    _int_avs->emplace_back(IntColumn());
    _int_offsets->emplace_back(IntColumn());
    _int_indizes->emplace_back(IntColumn());
  }
  else if (type == ColumnType::String) {
    if (!_string_columns) _string_columns = std::make_shared<std::vector<StringColumn>>();

    if (!_string_dictionaries) {
      _string_dictionaries = std::make_shared<std::vector<StringColumn>>();
      _string_avs = std::make_shared<std::vector<IntColumn>>();
      _string_offsets = std::make_shared<std::vector<IntColumn>>();
      _string_indizes = std::make_shared<std::vector<IntColumn>>();
    }

    auto& columns = *_string_columns;
    columns.emplace_back(StringColumn());
    columns[columns.size() - 1].reserve(num_rows);

    _string_dictionaries->emplace_back(StringColumn());
    _string_avs->emplace_back(IntColumn());
    _string_offsets->emplace_back(IntColumn());
    _string_indizes->emplace_back(IntColumn());
  }
}

void Table::_fill_int_column(const size_t index, const Distribution distribution, const uint32_t value_count,
        const uint32_t num_rows) {
  std::mt19937 generator(1337);

  switch (distribution) {
    case Distribution::Uniform : {
      std::uniform_int_distribution<uint32_t> dist(1, value_count);
      for (size_t i = 0; i < num_rows; i++) {
        (*_int_columns)[index].push_back(dist(generator));
      }
      break;
    }
    case Distribution::Normal : {
      std::cout << "Not supported yet.\n";
      break;
    }
  }

  // Make dictionary
  const std::set<uint32_t> set((*_int_columns)[index].cbegin(), (*_int_columns)[index].cend());
  (*_int_dictionaries)[index] = IntColumn(set.cbegin(), set.cend());

  //Make attribute vector
  for (const auto& number : (*_int_columns)[index]) {

    for (uint32_t i = 0; i < (*_int_dictionaries)[index].size(); i++) {
      if (number == (*_int_dictionaries)[index][i]) (*_int_avs)[index].push_back(i);
    }
  }

  // Make indizes and offsets
  for (const auto& number : (*_int_dictionaries)[index]) {
    (*_int_offsets)[index].push_back((*_int_indizes)[index].size());
    for (uint32_t i = 0; i < (*_int_columns)[index].size(); i++) {
      if (number == (*_int_columns)[index][i]) (*_int_indizes)[index].push_back(i);
    }
  }
  // Append last index position + 1 to avoid segmentation fault
  (*_int_offsets)[index].push_back((*_int_indizes)[index].size());

}

void Table::_fill_string_column(const size_t index, const Distribution distribution, const uint32_t value_count,
        const uint32_t num_rows) {
  std::mt19937 generator(1337);

  switch (distribution) {
    case Distribution::Uniform : {
      std::uniform_int_distribution<char> dist(65, static_cast<char>(65 + value_count - 1));

      for (size_t i = 0; i < num_rows; i++) {
        const char c = dist(generator);

        std::array<char, 10> string = {};
        for (size_t j = 0; j < 10; j++) {
          if (j < 6) string[j] = 'A';
          else string[j] = c;
        }
        (*_string_columns)[index].push_back(string);
      }
      break;
    }
    case Distribution::Normal : {
      std::cout << "Not supported yet.\n";
      break;
    }
  }

  const auto is_equal = [](String a, String b) {
    for (size_t i = 0; i < a.size(); i++) if (a[i] != b[i]) return false;
    return true;
  };

  // Make dictionary
  const std::set<String> set((*_string_columns)[index].cbegin(), (*_string_columns)[index].cend());
  (*_string_dictionaries)[index] = StringColumn(set.cbegin(), set.cend());

  //Make attribute vector
  for (const auto& str : (*_string_columns)[index]) {

    for (uint32_t i = 0; i < (*_string_dictionaries)[index].size(); i++) {
      if (is_equal(str, (*_string_dictionaries)[index][i])) (*_string_avs)[index].push_back(i);
    }
  }

  // Make indizes and offsets
  for (const auto& str : (*_string_dictionaries)[index]) {
    (*_string_offsets)[index].push_back((*_string_indizes)[index].size());
    for (uint32_t i = 0; i < (*_string_columns)[index].size(); i++) {
      if (is_equal((*_string_columns)[index][i], str)) (*_string_indizes)[index].push_back(i);
    }
  }
  // Append last index position + 1 to avoid segmentation fault
  (*_string_offsets)[index].push_back((*_string_indizes)[index].size());

}

}  // namespace indexvsscan
