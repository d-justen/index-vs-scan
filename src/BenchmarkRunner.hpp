#ifndef SRC_BENCHMARKRUNNER_HPP_
#define SRC_BENCHMARKRUNNER_HPP_

#include <memory>
#include <mutex>

#include "BenchmarkConfig.hpp"
#include "Table.hpp"

namespace indexvsscan {

class BenchmarkRunner {
 public:
  explicit BenchmarkRunner(const BenchmarkConfig config, std::shared_ptr<Table> table) :
    _config(config), _table(table) {}

  void execute();

 private:
  void _run_instruction(const Instruction& instruction);
  size_t _count_results(const std::shared_ptr<std::vector<char>> vec) const;
  void _append_result(const Result& result);
  void _print_results();

  const BenchmarkConfig _config;
  const std::shared_ptr<Table> _table;

  std::vector<Result> _results;
  std::mutex _results_mutex;
};

}  // namespace indexvsscan

#endif  // SRC_BENCHMARKRUNNER_HPP_
