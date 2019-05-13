#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>

#include "Table.hpp"
#include "Scan.hpp"
#include "BenchmarkConfig.hpp"
#include "BenchmarkRunner.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
  uint32_t num_rows = 10'000'000;
  if (argc > 1) num_rows *= std::atoi(argv[1]);

  std::mt19937 generator(1337);
  std::uniform_int_distribution<char> dist1(65, static_cast<char>(69));
  std::uniform_int_distribution<char> dist2(65, static_cast<char>(65));

  const BenchmarkConfig config {
    num_rows,  // Table length
    {
      ColumnDefinition(ColumnType::String, 5, Distribution::Uniform),  // Make one IntColumn with 4 distinct values
      ColumnDefinition(ColumnType::String, 1, Distribution::Uniform)  // + one StringColumn
    },
    {
      Instruction(ColumnType::String, 0, Operation::Equals, static_cast<uint32_t>(dist1(generator))),
      Instruction(ColumnType::String, 0, Operation::EqualsDict, static_cast<uint32_t>(dist1(generator))),
      Instruction(ColumnType::String, 0, Operation::EqualsIndex, static_cast<uint32_t>(dist1(generator))),
      Instruction(ColumnType::String, 1, Operation::Equals, static_cast<uint32_t>(dist2(generator))),
      Instruction(ColumnType::String, 1, Operation::EqualsDict, static_cast<uint32_t>(dist2(generator))),
      Instruction(ColumnType::String, 1, Operation::EqualsIndex, static_cast<uint32_t>(dist2(generator)))
    },
    1000  // 1000 runs TODO 100 * 1000?
  };
  const auto table = std::make_shared<Table>(config);
  BenchmarkRunner runner(config, table);
  runner.execute();

  return 0;
}
