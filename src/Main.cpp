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
  uint32_t num_rows = 1'000'000;
  uint32_t int_select;
  uint32_t string_select;
  if (argc > 1) num_rows *= std::atoi(argv[1]);
  if (argc > 2) int_select = std::atoi(argv[2]);
  if (argc > 3) string_select = std::atoi(argv[3]);

  const BenchmarkConfig config {
    num_rows,  // Table length
    {
      ColumnDefinition(ColumnType::String, 5, 0.2),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 1, 1),
      ColumnDefinition(ColumnType::Int, 5, 0.2),
      ColumnDefinition(ColumnType::Int, 1, 1)
    },
    {
      Instruction(ColumnType::String, 0, Operation::Equals, string_select),
      Instruction(ColumnType::String, 0, Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 0, Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 1, Operation::Equals, string_select),
      Instruction(ColumnType::String, 1, Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 1, Operation::EqualsIndex, string_select),
      Instruction(ColumnType::Int, 0, Operation::Equals, int_select),
      Instruction(ColumnType::Int, 0, Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 0, Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 1, Operation::Equals, int_select),
      Instruction(ColumnType::Int, 1, Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 1, Operation::EqualsIndex, int_select)
    },
    20  // 1000 runs TODO 100 * 1000?
  };
  const auto table = std::make_shared<Table>(config);
  BenchmarkRunner runner(config, table);
  runner.execute();

  return 0;
}
//TODO: papi