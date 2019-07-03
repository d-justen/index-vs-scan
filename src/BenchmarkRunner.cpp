#include "BenchmarkRunner.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>
#include <thread>
#include <tuple>

#include "Scan.hpp"

namespace indexvsscan {

void BenchmarkRunner::execute() {
  const auto run_instructions = [&](const std::vector<Instruction>& instructions, int from, const int to) {
    for (; from < to; from++) {
      _run_instruction(instructions[from]);
    }
  };

  const auto multiply_inst_ids = [&](std::vector<Instruction> instructions, const int mult) {
    for (auto& inst : instructions) {
      std::get<0>(inst) += mult * instructions.size();
    }
    return instructions;
  };

  std::vector<Instruction> all_instructions{};

  for (int i=0; i<_config.num_runs; i++) {
    const auto new_instrs = multiply_inst_ids(_config.instructions, i);
    all_instructions.insert(all_instructions.cend(), new_instrs.cbegin(), new_instrs.cend());
  }

  _results = std::vector<Result>(all_instructions.size());

  if (_config.multithreading) {
    std::vector<std::thread> threads{};

    for (int i = 0; i < _config.num_threads; i++) {
      const int from = _config.num_runs / _config.num_threads * i;
      const int to = _config.num_runs / _config.num_threads * (i+1);
      threads.emplace_back(std::thread(run_instructions, all_instructions, from, to));
    }
    for (auto &t : threads) {
      t.join();
    }
  }
  else {
    run_instructions(all_instructions, 0, all_instructions.size());
  }
  _print_results();
}

void BenchmarkRunner::_run_instruction(const Instruction& instruction) {
  const auto [id, column_type, index, operation, value] = instruction;
  if (column_type == ColumnType::Int) {
    switch (operation) {
      case Operation::Equals : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsDict : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_dict(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsDictBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_dict_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsIndex : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_index(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (elapsed_microseconds == 0) elapsed_microseconds = 1; //TODO
        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsIndexBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_index_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsBTree : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_eq_tree(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEquals : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsDict : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_dict(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsDictBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_dict_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsIndex : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_index(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsIndexBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_index_bitset(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsBTree : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.int_leq_tree(index, value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 4, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      default : std::cout << "Not supported yet.\n";
    }
  }
  else if (column_type == ColumnType::String) {
    const char c = static_cast<char>(value);
    String string_value = {};
    for(size_t i = 0; i < 10; i++) {
      if (i < 6) {
        string_value[i] = 'A';
      } else if (i < 9) {
        string_value[i] = '^';
      } else {
        string_value[i] = c;
      }
    }


    switch (operation) {
      case Operation::Equals : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsDict : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_dict(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsDictBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_dict_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsIndex : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_index(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (elapsed_microseconds == 0) elapsed_microseconds = 1; //TODO
        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::EqualsIndexBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_index_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::EqualsBTree : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_eq_tree(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEquals : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsDict : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_dict(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsDictBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_dict_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsIndex : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_index(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsIndexBitset : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_index_bitset(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();
        const auto cnt = _count_results(scan.get_result_bitset());
        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(_count_results(scan.get_result_bitset())) / _config.num_rows});
        break;
      }
      case Operation::LessOrEqualsBTree : {
        Scan scan(_table);
        const auto start = std::chrono::high_resolution_clock::now();
        scan.string_leq_tree(index, string_value);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        _append_result(Result{instruction, _config.num_rows, _config.num_rows * 10, elapsed_microseconds,
                              static_cast<double>(scan.get_result()->size()) / _config.num_rows});
        break;
      }
      default : std::cout << "Not supported yet.\n";
    }
  }
}

size_t BenchmarkRunner::_count_results(const std::shared_ptr<std::vector<char>> vec) const {
  size_t count = 0;
  for (const auto& b : *vec) count+= b;
  return count;
}

void BenchmarkRunner::_append_result(const Result& result) {
  const auto id = std::get<0>(result.instruction);
  _results[id] = result;
}

void BenchmarkRunner::_print_results() {
  std::ofstream file;
  file.open("out.csv");

  file << "column_type,index,operation,value,row_count,row_size_mb,selectivity,duration_microseconds,bandwidth_gb_s\n";

  for (size_t i = 0; i < _results.size(); i++) {
    const auto [id, column_type, index, operation, value] = _results[i].instruction;
    const auto byte_per_microsecond = (static_cast<double>(_results[i].num_bytes / std::max(_results[i].microseconds, 1L)));
    const auto gb_per_microsecond = byte_per_microsecond / std::pow(1000, 3);
    const auto gb_per_second = gb_per_microsecond * 1'000'000;

    const auto rows_count = _results[i].num_rows;
    file << static_cast<uint32_t>(column_type) << ","
         << index << ","
         << static_cast<uint32_t>(operation) << ","
         << value << ","
         << rows_count << ","
         << _results[i].num_bytes / static_cast<double>(1000 * 1000) << ","
         << std::round(_results[i].selectivity * 10'000) / 10'000.0 << ","
         << _results[i].microseconds << ","
         << gb_per_second << "\n";
  }

  file.close();
}

}  // namespace indexvsscan
