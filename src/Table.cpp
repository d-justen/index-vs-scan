#include "Table.hpp"

#include <chrono>
#include <iostream>
#include <random>

namespace indexvsscan {

Table::Table(const BenchmarkConfig& config) {
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

    auto& columns = *_int_columns;
    columns.emplace_back(IntColumn());
    columns[columns.size() - 1].reserve(num_rows);
  }
  else if (type == ColumnType::String) {
    if (!_string_columns) {
      _string_columns = std::make_shared<std::vector<StringColumn>>();
    }

    auto& columns = *_string_columns;
    columns.emplace_back(StringColumn());
    columns[columns.size() - 1].reserve(num_rows);
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
      /*
      std::normal_distribution<uint32_t> dist((value_count + 1) / 2, 1);
      for (size_t i = 0; i < num_rows; i++) {
        (*_int_columns)[index].push_back(dist(generator));
      }
      */
      std::cout << "Not supported yet.\n";
      break;
    }
  }
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
        for (size_t j = 0; j < 10; j++) string[j] = c;

        (*_string_columns)[index].push_back(string);
      }
      break;
    }
    case Distribution::Normal : {
      /*
      std::normal_distribution<char> dist(65 + (value_count + 1) / 2, 1);

      for (size_t i = 0; i < num_rows; i++) {
        const char c = dist(generator);

        std::array<char, 10> string = {};
        for (size_t j = 0; j < 10; j++) string[j] = c;

        (*_string_columns)[index].push_back(string);
      }
      */
      std::cout << "Not supported yet.\n";
      break;
    }
  }
}

}  // namespace indexvsscan
