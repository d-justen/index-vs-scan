#include "BenchmarkRunner.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>

#include "Scan.hpp"

namespace indexvsscan {

void BenchmarkRunner::execute() {
  for (const auto& instruction : _config.instructions) {
    const auto [column_type, index, operation, value] = instruction;

    if (column_type == ColumnType::Int) {
      switch (operation) {
        case Operation::Equals : {
          const Scan scan(_table);
          const auto& column = _table->get_int_column(index);

          size_t count = 0;
          size_t sum_elapsed = 0;
          for (size_t i = 0; i < _config.num_runs; i++) {
            const auto start = std::chrono::steady_clock::now();
            count = scan.int_eq(column, value);
            const auto end = std::chrono::steady_clock::now();

            const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            sum_elapsed += elapsed_microseconds;
          }
          _print_results(_config.num_rows * 4, static_cast<double>(sum_elapsed) / _config.num_runs, static_cast<double>(count) / _config.num_rows);
          break;
        }
        default : std::cout << "Not supported yet.\n";
      }
    }
    else if (column_type == ColumnType::String) {
      switch (operation) {
        case Operation::Equals : {
          const Scan scan(_table);
          const auto& column = _table->get_string_column(index);
          const char c = static_cast<char>(value);
          String string_value = {};
          for (size_t i = 0; i < 10; i++) string_value[i] = c;

          size_t count = 0;
          size_t sum_elapsed = 0;
          for (size_t i = 0; i < _config.num_runs; i++) {
            const auto start = std::chrono::steady_clock::now();
            count = scan.string_eq(column, string_value);
            const auto end = std::chrono::steady_clock::now();

            const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            sum_elapsed += elapsed_microseconds;
          }
          _print_results(_config.num_rows * 10, static_cast<double>(sum_elapsed) / _config.num_runs, static_cast<double>(count) / _config.num_rows);
          break;
        }
        default : std::cout << "Not supported yet.\n";
      }
    }

  }
}

void BenchmarkRunner::_print_results(const size_t data_size, const double duration, const double selectivity) {
  const auto byte_per_microsecond = (static_cast<double>(data_size / duration));
  const auto gb_per_microsecond = byte_per_microsecond / std::pow(1000, 3);
  const auto gb_per_sencond = gb_per_microsecond * 1'000'000;

  const auto rows_count = _config.num_rows;

  std::cout << "Rows: " << rows_count <<
            "\nSize: " << data_size / static_cast<double>(1000 * 1000) << " MB" <<
            "\nSelectivity: " << selectivity <<
            "\nDuration: " << static_cast<double>(duration) / 1'000 << " ms" <<
            "\nBandwith: " << gb_per_sencond << " GB/s\n\n";

  std::ofstream file;
  if (std::ifstream("out.csv").good()) {
    file.open("out.csv", std::ios::app);
  } else {
    file.open("out.csv");
  }
  file << _config.num_runs << ","
       << _config.num_rows << ","
       << duration << ","
       << gb_per_sencond << ","
       << selectivity << "\n";
  file.close();
}

}  // namespace indexvsscan