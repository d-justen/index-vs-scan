#ifndef SRC_BENCHMARKRUNNER_HPP_
#define SRC_BENCHMARKRUNNER_HPP_

#include <memory>

#include "BenchmarkConfig.hpp"
#include "Table.hpp"

namespace indexvsscan {

class BenchmarkRunner {
 public:
  explicit BenchmarkRunner(const BenchmarkConfig config, std::shared_ptr<Table> table) :
    _config(config), _table(table) {}

  void execute();

 private:
  void _print_results(size_t data_size, double duration, double selectivity);

  const BenchmarkConfig _config;
  const std::shared_ptr<Table> _table;
};

}  // namespace indexvsscan

#endif  // SRC_BENCHMARKRUNNER_HPP_
