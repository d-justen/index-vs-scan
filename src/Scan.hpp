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

 private:
  const std::shared_ptr<Table> _table;
};

}  // namespace indexvsscan

#endif // SRC_SCAN_HPP_
