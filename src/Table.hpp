#ifndef SRC_TABLE_HPP_
#define SRC_TABLE_HPP_

#include <cstdint>
#include <vector>
#include <array>
#include <memory>

#include "BenchmarkConfig.hpp"

namespace indexvsscan {

using String = std::array<char, 10>;
using IntColumn = std::vector<uint32_t>;
using StringColumn = std::vector<String>;

class Table {
 public:
  explicit Table(const BenchmarkConfig& config);
  Table(const Table&) = delete;

  IntColumn& get_int_column(uint32_t i) const { return _int_columns->at(i); }
  StringColumn& get_string_column(uint32_t i) const { return _string_columns->at(i); }

 private:

  void _make_column(ColumnType type, size_t num_rows);
  void _fill_int_column(size_t index, Distribution distribution, uint32_t value_count, uint32_t num_rows);
  void _fill_string_column(size_t index, Distribution distribution, uint32_t value_count, uint32_t num_rows);

  std::shared_ptr<std::vector<IntColumn>> _int_columns;
  std::shared_ptr<std::vector<StringColumn>> _string_columns;

};

}  // namespace indexvsscan

#endif  // SRC_TABLE_HPP_
