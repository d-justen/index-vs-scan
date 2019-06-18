#ifndef SRC_TABLE_HPP_
#define SRC_TABLE_HPP_

#include <cstdint>
#include <vector>
#include <array>
#include <memory>

#include "BenchmarkConfig.hpp"
#include "btree_map.h"

namespace indexvsscan {

using String = std::array<char, 10>;
using IntColumn = std::vector<uint8_t>;
using AVColumn = std::vector<uint8_t>;
using StringColumn = std::vector<String>;
using StringTree = btree::btree_multimap<String, uint32_t>;
using IntTree = btree::btree_multimap<uint32_t , uint32_t>;

class Table {
 public:
  explicit Table(const BenchmarkConfig& config);
  Table(const Table&) = delete;

  IntColumn& get_int_column(uint32_t i) const { return _int_columns->at(i); }
  IntColumn& get_int_dictionary(uint32_t i) const { return _int_dictionaries->at(i); }
  IntColumn& get_int_attribute_vector(uint8_t i) const { return _int_avs->at(i); }
  std::vector<uint32_t>& get_int_offset(uint32_t i) const { return _int_offsets->at(i); }
  std::vector<uint32_t>& get_int_indizes(uint32_t i) const { return _int_indizes->at(i); }
  IntTree& get_int_tree(uint32_t i) const { return _int_trees->at(i); }

  StringColumn& get_string_column(uint32_t i) const { return _string_columns->at(i); }
  StringColumn& get_string_dictionary(uint32_t i) const { return _string_dictionaries->at(i); }
  IntColumn& get_string_attribute_vector(uint8_t i) const { return _string_avs->at(i); }
  std::vector<uint32_t>& get_string_offset(uint32_t i) const { return _string_offsets->at(i); }
  std::vector<uint32_t>& get_string_indizes(uint32_t i) const { return _string_indizes->at(i); }
  StringTree& get_string_tree(uint32_t i) const { return _string_trees->at(i); }

  const size_t num_rows;

 private:

  void _make_column(ColumnType type, size_t num_rows);
  void _fill_int_column(size_t index, uint32_t value_count, OperationType operation_type, double selectivity, uint32_t num_rows, uint8_t value);
  void _fill_string_column(size_t index, uint32_t value_count, OperationType  operation_type, double selectivity, uint32_t num_rows, uint8_t value);

  std::shared_ptr<std::vector<IntColumn>> _int_columns;
  std::shared_ptr<std::vector<IntColumn>> _int_dictionaries;
  std::shared_ptr<std::vector<IntColumn>> _int_avs;
  std::shared_ptr<std::vector<std::vector<uint32_t>>> _int_offsets;
  std::shared_ptr<std::vector<std::vector<uint32_t>>> _int_indizes;
  std::shared_ptr<std::vector<IntTree>> _int_trees;

  std::shared_ptr<std::vector<StringColumn>> _string_columns;
  std::shared_ptr<std::vector<StringColumn>> _string_dictionaries;
  std::shared_ptr<std::vector<IntColumn>> _string_avs;
  std::shared_ptr<std::vector<std::vector<uint32_t>>> _string_offsets;
  std::shared_ptr<std::vector<std::vector<uint32_t>>> _string_indizes;
  std::shared_ptr<std::vector<StringTree>> _string_trees;

};

}  // namespace indexvsscan

#endif  // SRC_TABLE_HPP_
