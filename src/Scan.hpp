#ifndef SRC_SCAN_HPP_
#define SRC_SCAN_HPP_

#include <vector>
#include <array>
#include <memory>
#include <cstdint>
#include "Table.hpp"

namespace indexvsscan {

class Scan {
 public:
  Scan(const std::shared_ptr<Table> table) : _table(table) {}

  size_t scan_gt(size_t gt);

  size_t scan_contains_char(char c);

  size_t scan_gt_and_contains(size_t gt, char c);

 private:
  void _print_results(size_t data_size, double duration, double selectivity);

  const std::shared_ptr<Table> _table;
};

}  // namespace indexvsscan

#endif // SRC_SCAN_HPP_
