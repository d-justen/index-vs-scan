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

// TODO: 1 table, 5 mia zeilen, 10% selektivität, 2 byte int werte, poslist,
// TODO: Attributvektor kleiner machen
  const BenchmarkConfig config {
    TABLE_LENGTH,  // Table length muss zur compile time bekannt sein, weil größe der bitsets zur compile time bekannt sein muss
    {
      ColumnDefinition(ColumnType::Int, 100, 0.1, int_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
    },
    {
      Instruction(ColumnType::Int, 0,  Operation::Equals, int_select),
    },
    1 // 1000 runs TODO 100 * 1000?
  };
  const auto table = std::make_shared<Table>(config);
  BenchmarkRunner runner(config, table);
  runner.execute();

  return 0;
}
//TODO: papi