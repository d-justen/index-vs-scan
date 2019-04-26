#include "Scan.hpp"

#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

size_t Scan::scan_gt(const size_t gt) {
  const auto column_1 = _table->get_column_1();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < column_1->size(); i++) {
    if (column_1->at(i) > gt) count++;
  }

  const auto end = std::chrono::steady_clock::now();

  const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  const auto byte_per_microsecond = (static_cast<double>(column_1->size()) * 4 / elapsed_microseconds);
  const auto gb_per_microsecond = byte_per_microsecond / std::pow(1024, 3);
  const auto gb_per_sencond = gb_per_microsecond * 1'000'000;

  std::cout << "Rows: " << column_1->size() <<
            "\nSize: " << column_1->size() * 4 / static_cast<double>(1024 * 1024) << " MB" <<
            "\nSelectivity: " << static_cast<double>(count) / column_1->size() <<
            "\nDuration: " << static_cast<double>(elapsed_microseconds) / 1'000 << " ms" <<
            "\nBandwith: " << gb_per_sencond << " GB/s\n";


  return count;
}

size_t Scan::scan_contains_char(const char c) {
  const auto column_2 = _table->get_column_2();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < column_2->size(); i++) {
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
  const auto byte_per_microsecond = (static_cast<double>(column_2->size()) * 10 / elapsed_microseconds);
  const auto gb_per_microsecond = byte_per_microsecond / std::pow(1024, 3);
  const auto gb_per_sencond = gb_per_microsecond * 1'000'000;

  std::cout << "Rows: " << column_2->size() <<
            "\nSize: " << column_2->size() * 10 / static_cast<double>(1024 * 1024) << " MB" <<
            "\nSelectivity: " << static_cast<double>(count) / column_2->size() <<
            "\nDuration: " << static_cast<double>(elapsed_microseconds) / 1'000 << " ms" <<
            "\nBandwith: " << gb_per_sencond << " GB/s\n";


  return count;
}

size_t Scan::scan_gt_and_contains(const size_t gt, const char c) {
  const auto column_1 = _table->get_column_1();
  const auto column_2 = _table->get_column_2();

  const auto start = std::chrono::steady_clock::now();

  size_t count = 0;
  for (size_t i = 0; i < column_2->size(); i++) {
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
  const auto byte_per_microsecond = (static_cast<double>(column_2->size()) * 14 / elapsed_microseconds);
  const auto gb_per_microsecond = byte_per_microsecond / std::pow(1024, 3);
  const auto gb_per_sencond = gb_per_microsecond * 1'000'000;

  std::cout << "Rows: " << column_2->size() <<
            "\nSize: " << column_2->size() * 14 / static_cast<double>(1024 * 1024) << " MB" <<
            "\nSelectivity: " << static_cast<double>(count) / column_2->size() <<
            "\nDuration: " << static_cast<double>(elapsed_microseconds) / 1'000 << " ms" <<
            "\nBandwith: " << gb_per_sencond << " GB/s\n";


  return count;
}

}  // namespace indexvsscan
