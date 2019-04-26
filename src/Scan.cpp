#include "Scan.hpp"

#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

size_t Scan::scan_gt(const size_t gt) {
  std::cout << "### Scan for values > " << gt << " ###\n";

  const auto column_1 = _table->get_column_1();
  const auto rows_count = _table->get_column_1()->size();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < rows_count; i++) {
    if (column_1->at(i) > gt) count++;
  }

  const auto end = std::chrono::steady_clock::now();

  const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  _print_results(rows_count * 4, elapsed_microseconds, static_cast<double>(count) / rows_count);

  return count;
}

size_t Scan::scan_contains_char(const char c) {
  std::cout << "\n### Scan for values containing '" << std::string(1, c) << "' ###\n";

  const auto column_2 = _table->get_column_2();
  const auto rows_count = _table->get_column_1()->size();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < rows_count; i++) {
    auto char_arr = column_2->at(i);
    for (size_t j = 0; j < char_arr.size(); j++) {
      if (c == char_arr[j]) {
        count ++;
        break;
      }
    }
  }

  const auto end = std::chrono::steady_clock::now();

  const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  _print_results(rows_count * 10, elapsed_microseconds, static_cast<double>(count) / rows_count);

  return count;
}

size_t Scan::scan_gt_and_contains(const size_t gt, const char c) {
  std::cout << "\n### Scan for values > " << gt << " and containing '" << std::string(1, c) << "' ###\n";

  const auto column_1 = _table->get_column_1();
  const auto column_2 = _table->get_column_2();
  const auto rows_count = _table->get_column_1()->size();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < rows_count; i++) {
    if (column_1->at(i) > gt) {
      auto char_arr = column_2->at(i);

      for (size_t j = 0; j < char_arr.size(); j++) {
        if (c == char_arr[j]) {
          count ++;
          break;
        }
      }
    }
  }

  const auto end = std::chrono::steady_clock::now();

  const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  _print_results(rows_count * 14, elapsed_microseconds, static_cast<double>(count) / rows_count);

  return count;
}

void Scan::_print_results(const size_t data_size, const double duration, const double selectivity) {
  const auto byte_per_microsecond = (static_cast<double>(data_size / duration));
  const auto gb_per_microsecond = byte_per_microsecond / std::pow(1024, 3);
  const auto gb_per_sencond = gb_per_microsecond * 1'000'000;

  const auto rows_count = _table->get_column_1()->size();

  std::cout << "Rows: " << rows_count <<
            "\nSize: " << data_size / static_cast<double>(1024 * 1024) << " MB" <<
            "\nSelectivity: " << selectivity <<
            "\nDuration: " << static_cast<double>(duration) / 1'000 << " ms" <<
            "\nBandwith: " << gb_per_sencond << " GB/s\n";
}

}  // namespace indexvsscan
