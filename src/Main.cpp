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

    const uint32_t table_length = std::atol(argv[1]);
    std::cout << "Table length: " << table_length << "\n";

    std::string argv2 = argv[2];
    const bool is_int = argv2 == "int";

    std::cout << "Column size: " << (is_int ? 4 * table_length / 1'000'000 : 10 * table_length / 1'000'000) << " MB\n";

    std::string argv3 = argv[3];
    const bool multithreading = argv3 == "mt";

    std::cout << "Multithreading: " << (multithreading ? "ON" : "OFF") << "\n";
    uint32_t num_runs = std::atoi(argv[4]);
    uint32_t num_distinct_vals = std::atoi(argv[5]);

    std::string argv6 = argv[6];
    const bool leq = argv6 == "leq";

    uint32_t select = string_dist(generator);
    ColumnType ct = ColumnType::String;
    if (is_int) {
        ct = ColumnType::Int;
        select = int_dist(generator);
    }

    OperationType opt = OperationType::Equals;
    if (leq) {
        opt = OperationType::LessOrEquals;
    }

    std::vector<ColumnDefinition> definitions{};
    definitions.push_back(ColumnDefinition(ct, num_distinct_vals, opt, 0.0001, select));
    double max_selectivity = leq ? 1 : static_cast<double>((table_length - num_distinct_vals)) / table_length;
    for (int i=0; i<15; i++) {
        definitions.push_back(ColumnDefinition(ct, num_distinct_vals, opt, static_cast<double>(i+1) / 15 * max_selectivity, select));
    }

    std::vector<Instruction> instructions{};
    int begin_op = leq ? 7 : 0;
    int end_op = leq ? 14 : 7;

    for (; begin_op < end_op; begin_op++) {
        for (int i = 0; i < 16; i++) {
            instructions.push_back(Instruction(ct, i, Operation{begin_op}, select));
        }
    }

    const BenchmarkConfig config {
        table_length,
        definitions,
        instructions,
        num_runs,
        multithreading
    };
    const auto table = std::make_shared<Table>(config);
    BenchmarkRunner runner(config, table);
    runner.execute();

    return 0;
}
