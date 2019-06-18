#ifndef SRC_SCAN_HPP_
#define SRC_SCAN_HPP_

#include <bitset>
#include <vector>
#include <array>
#include <memory>
#include <cstdint>
#include "Table.hpp"
#include "BenchmarkConfig.hpp"

namespace indexvsscan {

class Scan {
 public:
  Scan(const std::shared_ptr<Table> table);

  void int_eq(uint32_t id, uint8_t value);
  void int_eq_bitset(uint32_t id, uint8_t value);
  void int_eq_dict(uint32_t id, uint8_t value);
  void int_eq_dict_bitset(uint32_t id, uint8_t value);
  void int_eq_index(uint32_t id, uint8_t value);
  void int_eq_tree(uint32_t id, uint8_t value);

  void string_eq(uint32_t id, const String& value);
  void string_eq_bitset(uint32_t id, const String& value);
  void string_eq_dict(uint32_t id, const String& value);
  void string_eq_dict_bitset(uint32_t id, const String& value);
  void string_eq_index(uint32_t id, const String& value);
  void string_eq_tree(uint32_t id, const String& value);

  void int_leq(uint32_t id, uint8_t value);
  void int_leq_bitset(uint32_t id, uint8_t value);
  void int_leq_dict(uint32_t id, uint8_t value);
  void int_leq_dict_bitset(uint32_t id, uint8_t value);
  void int_leq_index(uint32_t id, uint8_t value);
  void int_leq_tree(uint32_t id, uint8_t value);

  void string_leq(uint32_t id, const String& value);
  void string_leq_bitset(uint32_t id, const String& value);
  void string_leq_dict(uint32_t id, const String& value);
  void string_leq_dict_bitset(uint32_t id, const String& value);
  void string_leq_index(uint32_t id, const String& value);
  void string_leq_tree(uint32_t id, const String& value);

  const std::shared_ptr<std::vector<uint32_t>> get_result() { return _result; };
  const std::shared_ptr<std::vector<bool>> get_result_bitset() { return _result_bitset; }
/*
  size_t scan_gt(size_t gt);

  size_t scan_contains_char(char c);

  size_t scan_gt_and_contains(size_t gt, char c);
*/
 private:
  const std::shared_ptr<Table> _table;
  const std::shared_ptr<std::vector<uint32_t>> _result;
  const std::shared_ptr<std::vector<bool>> _result_bitset;

};

}  // namespace indexvsscan

#endif // SRC_SCAN_HPP_
