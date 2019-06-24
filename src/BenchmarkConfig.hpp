#ifndef SRC_BENCHMARKCONFIG_HPP_
#define SRC_BENCHMARKCONFIG_HPP_

#include <vector>
#include <tuple>

namespace indexvsscan {

constexpr uint32_t TABLE_LENGTH = 1'000'000;

enum class ColumnType { Int, String };
enum class Operation {
  Equals,
  EqualsBitset,
  EqualsDict,
  EqualsDictBitset,
  EqualsIndex,
  EqualsIndexBitset,
  EqualsBTree,
  LessOrEquals,
  LessOrEqualsBitset,
  LessOrEqualsDict,
  LessOrEqualsDictBitset,
  LessOrEqualsIndex,
  LessOrEqualsIndexBitset,
  LessOrEqualsBTree
};
enum class OperationType { Equals, LessOrEquals };

using ValueCount = uint32_t;
using Selectivity = double;
using Value = uint32_t;
using ColumnDefinition = std::tuple<ColumnType, ValueCount, OperationType , Selectivity, Value>;

// 1. Which column type 2. Index of column 3. which operation 4. value to compare
// Note: if ColumnType::String uint32_t is converted to char ten times
using Instruction = std::tuple<ColumnType, uint32_t, Operation, uint32_t>;

struct BenchmarkConfig {
  uint32_t num_rows;
  std::vector<ColumnDefinition> column_definitions;
  std::vector<Instruction> instructions;
  uint32_t num_runs;
};

struct Result {
  Instruction instruction;
  uint32_t num_rows;
  uint32_t num_bytes;
  long microseconds;
  double selectivity;
};

}  // namespace indexvsscan

#endif // SRC_BENCHMARKCONFIG_HPP_
