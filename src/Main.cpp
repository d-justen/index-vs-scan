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

    const uint32_t table_length = std::atol(argv[1]);
    std::cout << "Table length: " << table_length << "\n";
    const bool is_int = std::atoi(argv[2]) == 0;
    std::cout << "Column size: " << (is_int ? 4 * table_length / 1'000'000 : 10 * table_length / 1'000'000) << " MB\n";
    const bool multithreading = std::atoi(argv[3]) != 0;
    std::cout << "Multithreading: " << (multithreading ? "ON" : "OFF") << "\n";
    uint32_t num_runs = std::atoi(argv[4]);
    uint32_t num_distinct_vals = std::atoi(argv[5]);

    std::vector<ColumnDefinition> definitions {
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.05,  is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.075, is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.1,   is_int ? int_select : string_select),  // Make one StringColumn with 5 distinct values and selectivity 0.2
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.125, is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.15,  is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.2,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.25,  is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.3,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.4,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.45,  is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.5,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.55,  is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.6,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.8,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.9,   is_int ? int_select : string_select),
        ColumnDefinition(is_int ? ColumnType::Int : ColumnType::String, num_distinct_vals, OperationType::LessOrEquals, 0.95,  is_int ? int_select : string_select),
    };

    std::vector<Instruction> instructions {
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEquals, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEquals, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsBitset, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsDict, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsDict, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsDictBitset, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsIndex, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsIndexBitset, is_int ? int_select : string_select),

        Instruction(is_int ? ColumnType::Int : ColumnType::String, 0,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 1,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 2,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 3,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 4,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 5,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 6,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 7,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 8,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 9,  Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 10, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 11, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 12, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 13, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 14, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
        Instruction(is_int ? ColumnType::Int : ColumnType::String, 15, Operation::LessOrEqualsBTree, is_int ? int_select : string_select),
    };

    const BenchmarkConfig config {
        table_length,  // Table length muss zur compile time bekannt sein, weil größe der bitsets zur compile time bekannt sein muss
        definitions,
        instructions,
        num_runs, // 1000 runs TODO 100 * 1000?
        multithreading
    };
    const auto table = std::make_shared<Table>(config);
    BenchmarkRunner runner(config, table);
    runner.execute();

    return 0;
}
//TODO: papi