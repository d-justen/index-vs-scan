#include "Table.hpp"

#include <chrono>
#include <iostream>
#include <random>

namespace indexvsscan {

Table::Table(const uint32_t num_rows) {
  std::cout << "### Create table: 2 colums, " << num_rows << " random rows ###\n";

  const auto start = std::chrono::steady_clock::now();

  _column_1 = std::make_shared<std::vector<u_int32_t>>();
  _column_1->reserve(num_rows);

  _column_2 = std::make_shared<std::vector<std::array<char, 10>>>();
  _column_2->reserve(num_rows);

  std::mt19937 generator(1337);  // any generator for random values with seed 1337
  std::uniform_int_distribution<uint32_t > c1_dist(0, UINT32_MAX);
  std::uniform_int_distribution<char> c2_dist(65, 126);

  // Fill the vectors
  for (size_t i = 0; i < num_rows; i++) {
    _column_1->push_back(c1_dist(generator));

    std::array<char, 10> column_2_entry = {};
    for (size_t j = 0; j < 10; j++) column_2_entry[j] = c2_dist(generator);
    _column_2->push_back(column_2_entry);
  }

  const auto end = std::chrono::steady_clock::now();
  const auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
  std::cout << "Created table in " << duration << " seconds.\n\n";
}

}  // namespace indexvsscan
