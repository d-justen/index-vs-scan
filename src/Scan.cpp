#include "Scan.hpp"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

Scan::Scan(const std::shared_ptr<Table> table) : _table(table),
                                                 _result(std::make_shared<std::vector<uint32_t>>()),
                                                 _result_bitset(std::make_shared<std::vector<bool>>()) {
  _result->reserve(table->num_rows);
  _result_bitset->reserve(TABLE_LENGTH);
}

void Scan::int_eq(const uint32_t id, const uint32_t value) {
  const auto& column = _table->get_int_column(id);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (column[i] == value) result_ref.push_back(i);
  }
}

void Scan::int_eq_bitset(const uint32_t id, const uint32_t value) {
  const auto& column = _table->get_int_column(id);

  auto& result_ref = *_result_bitset;

  for (uint32_t i = 0; i < column.size(); i++) {
    result_ref.push_back(column[i] == value);
  }
}

void Scan::int_eq_dict(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& av = _table->get_int_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i  < av.size(); i++) {
    if (av[i] == distance) result_ref.push_back(i);
  }
}

void Scan::int_eq_dict_bitset(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& av = _table->get_int_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset;

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref.push_back(av[i] == distance);
  }
}

void Scan::int_eq_index(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& offsets = _table->get_int_offset(id);
  const auto& indizes = _table->get_int_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  const auto index_begin = indizes.cbegin() + offsets[distance];
  const auto index_end = indizes.cbegin() + offsets[distance+1];

  result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

void Scan::string_eq(const uint32_t id, const String& value) {
  const auto is_equal = [](const String& a, const String& b) {
    for (int i = 0; i < a.size(); i++) if (a[i] != b[i]) return false;
    return true;
  };

  const auto& column = _table->get_string_column(id);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (is_equal(column[i], value))
      result_ref.push_back(i);
  }
}

void Scan::string_eq_bitset(const uint32_t id, const String& value) {
  const auto is_equal = [](const String& a, const String& b) {
    return a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3] && a[4] == b[4] &&
           a[5] == b[5] && a[6] == b[6] && a[7] == b[7] && a[8] == b[8] && a[9] == b[9];
  };

  const auto& column = _table->get_string_column(id);

  auto& result_ref = *_result_bitset;

  for (uint32_t i = 0; i < column.size(); i++) {
    result_ref.push_back(is_equal(column[i], value));
  }
}

void Scan::string_eq_dict(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& av = _table->get_string_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i  < av.size(); i++) {
    if (av[i] == distance) result_ref.push_back(i);
  }
}

void Scan::string_eq_dict_bitset(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& av = _table->get_string_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset;

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref.push_back(av[i] == distance);
  }
}

void Scan::string_eq_index(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& offsets = _table->get_string_offset(id);
  const auto& indizes = _table->get_string_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  const auto index_begin = indizes.cbegin() + offsets[distance];
  const auto index_end = indizes.cbegin() + offsets[distance+1];

  result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

}  // namespace indexvsscan
