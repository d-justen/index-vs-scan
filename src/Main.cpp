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
    std::uniform_int_distribution<uint32_t> int_dist((UINT32_MAX / 2) - 1000, (UINT32_MAX / 2) + 1000);
    std::uniform_int_distribution<uint32_t> string_dist(90, 96);
    uint32_t int_select = int_dist(generator);
    uint32_t string_select = string_dist(generator);


  const BenchmarkConfig config {
    TABLE_LENGTH,  // Table length muss zur compile time bekannt sein, weil größe der bitsets zur compile time bekannt sein muss
    {
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.05,  string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.075, string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.1,   string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.125, string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.15,  string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.2,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.25,  string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.3,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.4,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.45,  string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.5,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.55,  string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.6,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.8,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.9,   string_select),
      ColumnDefinition(ColumnType::String, 10'000'000, OperationType::LessOrEquals, 0.95,  string_select),

      /*ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.05,  int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.075, int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.1,   int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.125, int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.15,  int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.2,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.25,  int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.3,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.4,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.45,  int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.5,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.55,  int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.6,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.8,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.9,   int_select),
      ColumnDefinition(ColumnType::Int, 10'000'000, OperationType::LessOrEquals, 0.95,  int_select),*/

    },
    {
      //Instruction(ColumnType::String, 0,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 1,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 2,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 3,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 4,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 5,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 6,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 7,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 8,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 9,  Operation::Equals, string_select),
      //Instruction(ColumnType::String, 10, Operation::Equals, string_select),

      /*Instruction(ColumnType::String, 0,  Operation::EqualsBitset, string_select),
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
      //Instruction(ColumnType::Int, 10, Operation::EqualsBTree, int_select),*/

      Instruction(ColumnType::String, 0,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEquals, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEquals, string_select),

      Instruction(ColumnType::String, 0,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEqualsBitset, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEqualsBitset, string_select),

      Instruction(ColumnType::String, 0,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEqualsDict, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEqualsDict, string_select),

      Instruction(ColumnType::String, 0,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEqualsDictBitset, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEqualsDictBitset, string_select),

      Instruction(ColumnType::String, 0,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEqualsIndex, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEqualsIndex, string_select),

      Instruction(ColumnType::String, 0,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 1,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 2,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 3,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 4,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 5,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 6,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 7,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 8,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 9,  Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 10, Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 11, Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 12, Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 13, Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 14, Operation::LessOrEqualsBTree, string_select),
      Instruction(ColumnType::String, 15, Operation::LessOrEqualsBTree, string_select),

      /*Instruction(ColumnType::Int, 0,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEquals, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEquals, int_select),

      Instruction(ColumnType::Int, 0,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEqualsBitset, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEqualsBitset, int_select),

      Instruction(ColumnType::Int, 0,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEqualsDict, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEqualsDict, int_select),

      Instruction(ColumnType::Int, 0,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEqualsDictBitset, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEqualsDictBitset, int_select),

      Instruction(ColumnType::Int, 0,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEqualsIndex, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEqualsIndex, int_select),

      Instruction(ColumnType::Int, 0,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 1,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 2,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 3,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 4,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 5,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 6,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 7,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 8,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 9,  Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 10, Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 11, Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 12, Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 13, Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 14, Operation::LessOrEqualsBTree, int_select),
      Instruction(ColumnType::Int, 15, Operation::LessOrEqualsBTree, int_select),*/

},
1000 // 1000 runs TODO 100 * 1000?
};
const auto table = std::make_shared<Table>(config);
BenchmarkRunner runner(config, table);
runner.execute();

return 0;
}
//TODO: papi