#ifndef SRC_TABLE_HPP_
#define SRC_TABLE_HPP_

#include <cstdint>
#include <vector>
#include <array>
#include <memory>

namespace indexvsscan {

class Table {
 public:
  Table(uint32_t num_rows);

  std::shared_ptr<std::vector<uint32_t>> get_column_1() { return _column_1; }
  std::shared_ptr<std::vector<std::array<char, 10>>> get_column_2() { return _column_2; }

 private:
  std::shared_ptr<std::vector<uint32_t>> _column_1;
  std::shared_ptr<std::vector<std::array<char, 10>>> _column_2;
};

}  // namespace indexvsscan

#endif  // SRC_TABLE_HPP_
