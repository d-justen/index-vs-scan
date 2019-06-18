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
    std::mt19937 generator(1337);
    std::uniform_int_distribution<uint32_t> int_dist(0, UINT32_MAX);
    std::uniform_int_distribution<uint32_t> string_dist(65, 123);
    uint32_t int_select = int_dist(generator);
    uint32_t string_select = string_dist(generator);


  const BenchmarkConfig config {
    TABLE_LENGTH,  // Table length muss zur compile time bekannt sein, weil größe der bitsets zur compile time bekannt sein muss
    {
      ColumnDefinition(ColumnType::String, 10, 0.01, string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 10, 0.1, string_select),
      ColumnDefinition(ColumnType::String, 10, 0.2, string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 10, 0.3, string_select),
      ColumnDefinition(ColumnType::String, 10, 0.4, string_select),
      ColumnDefinition(ColumnType::String, 10, 0.5, string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 10, 0.6, string_select),
      ColumnDefinition(ColumnType::String, 10, 0.7, string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 10, 0.8, string_select),
      ColumnDefinition(ColumnType::String, 10, 0.9, string_select),

      ColumnDefinition(ColumnType::Int, 10, 0.01, int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::Int, 10, 0.1, int_select),
      ColumnDefinition(ColumnType::Int, 10, 0.2, int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::Int, 10, 0.3, int_select),
      ColumnDefinition(ColumnType::Int, 10, 0.4, int_select),
      ColumnDefinition(ColumnType::Int, 10, 0.5, int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::Int, 10, 0.6, int_select),
      ColumnDefinition(ColumnType::Int, 10, 0.7, int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::Int, 10, 0.8, int_select),
      ColumnDefinition(ColumnType::Int, 10, 0.9, int_select),
    },
    {
      Instruction(ColumnType::String, 0,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 1,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 2,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 3,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 4,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 5,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 6,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 7,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 8,  Operation::Equals, string_select),
      Instruction(ColumnType::String, 9,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 10, Operation::Equals, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsBitset, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsBitset, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsBitset, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsDict, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsDict, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsDict, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsDictBitset, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsDictBitset, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsDictBitset, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsIndex, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsIndex, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsIndex, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsIndexBitset, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsIndexBitset, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsIndex, string_select),

      Instruction(ColumnType::String, 0,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 1,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 2,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 3,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 4,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 5,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 6,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 7,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 8,  Operation::EqualsBTree, string_select),
      Instruction(ColumnType::String, 9,  Operation::EqualsBTree, string_select),
      //Instruction(ColumnType::String, 10, Operation::EqualsBTree, string_select),

      Instruction(ColumnType::Int, 0,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 1,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 2,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 3,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 4,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 5,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 6,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 7,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 8,  Operation::Equals, int_select),
      Instruction(ColumnType::Int, 9,  Operation::Equals, int_select),
      //Instruction(ColumnType::Int, 10, Operation::Equals, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsBitset, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsBitset, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsBitset, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsDict, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsDict, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsDict, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsDictBitset, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsDictBitset, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsIndex, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsIndex, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsIndex, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsIndexBitset, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsIndexBitset, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsIndex, int_select),

      Instruction(ColumnType::Int, 0,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 1,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 2,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 3,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 4,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 5,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 6,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 7,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 8,  Operation::EqualsBTree, int_select),
      Instruction(ColumnType::Int, 9,  Operation::EqualsBTree, int_select),
      //Instruction(ColumnType::Int, 10, Operation::EqualsBTree, int_select),
    },
    100 // 1000 runs TODO 100 * 1000?
  };
  const auto table = std::make_shared<Table>(config);
  BenchmarkRunner runner(config, table);
  runner.execute();

  return 0;
}
//TODO: papi