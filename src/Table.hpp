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
using AVColumn = std::vector<uint8_t>;
using StringColumn = std::vector<String>;

class Table {
 public:
  explicit Table(const BenchmarkConfig& config);
  Table(const Table&) = delete;

  IntColumn& get_int_column(uint32_t i) const { return _int_columns->at(i); }
  IntColumn& get_int_dictionary(uint32_t i) const { return _int_dictionaries->at(i); }
  AVColumn& get_int_attribute_vector(uint8_t i) const { return _int_avs->at(i); }
  IntColumn& get_int_offset(uint32_t i) const { return _int_offsets->at(i); }
  IntColumn& get_int_indizes(uint32_t i) const { return _int_indizes->at(i); }

  StringColumn& get_string_column(uint32_t i) const { return _string_columns->at(i); }
  StringColumn& get_string_dictionary(uint32_t i) const { return _string_dictionaries->at(i); }
  AVColumn& get_string_attribute_vector(uint8_t i) const { return _string_avs->at(i); }
  IntColumn& get_string_offset(uint32_t i) const { return _string_offsets->at(i); }
  IntColumn& get_string_indizes(uint32_t i) const { return _string_indizes->at(i); }

  const size_t num_rows;

 private:

  void _make_column(ColumnType type, size_t num_rows);
  void _fill_int_column(size_t index, uint32_t value_count, double selectivity, uint32_t num_rows);
  void _fill_string_column(size_t index, uint32_t value_count, double selectivity, uint32_t num_rows);

  std::shared_ptr<std::vector<IntColumn>> _int_columns;
  std::shared_ptr<std::vector<IntColumn>> _int_dictionaries;
  std::shared_ptr<std::vector<std::vector<uint8_t>>> _int_avs;
  std::shared_ptr<std::vector<IntColumn>> _int_offsets;
  std::shared_ptr<std::vector<IntColumn>> _int_indizes;

  std::shared_ptr<std::vector<StringColumn>> _string_columns;
  std::shared_ptr<std::vector<StringColumn>> _string_dictionaries;
  std::shared_ptr<std::vector<std::vector<uint8_t>>> _string_avs;
  std::shared_ptr<std::vector<IntColumn>> _string_offsets;
  std::shared_ptr<std::vector<IntColumn>> _string_indizes;

};

}  // namespace indexvsscan

#endif  // SRC_TABLE_HPP_
