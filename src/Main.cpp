#include <cstdlib>
#include <iostream>
#include <memory>
#include "Table.hpp"
#include "Scan.hpp"
#include "BenchmarkConfig.hpp"
#include "BenchmarkRunner.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
  size_t num_rows = 1'000'000;
  if (argc > 1) num_rows *= std::atoi(argv[1]);

  const BenchmarkConfig config {
    1'000'000,  // Table length
    {
      ColumnDefinition(ColumnType::Int, 4, Distribution::Uniform),  // Make one IntColumn with 4 distinct values
      ColumnDefinition(ColumnType::String, 6, Distribution::Uniform)  // + one StringColumn
    },
    {
      Instruction(ColumnType::Int, 0, Operation::Equals, 2),  // In IntColumn[0] find all values == 2
      Instruction(ColumnType::String, 0, Operation::Equals, static_cast<uint32_t>('B'))
    },
    50  // 50 runs
  };
  const auto table = std::make_shared<Table>(config);
  BenchmarkRunner runner(config, table);
  runner.execute();

  return 0;
}
