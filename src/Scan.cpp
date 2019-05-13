#include "Scan.hpp"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

void Scan::int_eq(const IntColumn& column, const uint32_t value) {
  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (column[i] == value) result_ref.push_back(i);
  }
}

void Scan::string_eq(const StringColumn& column, const String value) {
  const auto is_equal = [](String a, String b) {
    for (int i = 0; i < a.size(); i++) if (a[i] != b[i]) return false;
    return true;
  };

  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (is_equal(column[i], value))
      result_ref.push_back(i);
  }
}

void Scan::string_eq_index(const uint32_t id, const String value) {
  const auto& dict = _table->get_dictionary(id);
  const auto& offsets = _table->get_offset(id);
  const auto& indizes = _table->get_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  for (size_t i = offsets[distance]; i < offsets[distance+1]; i++) {
    result_ref.push_back(indizes[i]);
  }
}

void Scan::string_eq_dict(const uint32_t id, const String value) {
  const auto& dict = _table->get_dictionary(id);
  const auto& av = _table->get_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i  < av.size(); i++) {
    if (av[i] == distance) result_ref.push_back(i);
  }
}

}  // namespace indexvsscan
