#include "Scan.hpp"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

Scan::Scan(const std::shared_ptr<Table> table) : _table(table),
                                                 _result(std::make_shared<std::vector<uint32_t>>()),
                                                 _result_bitset(std::make_shared<std::vector<uint8_t>>()),
                                                 _result_bitset_init(std::make_shared<std::vector<uint8_t>>(TABLE_LENGTH)){
  _result->reserve(TABLE_LENGTH);
  _result_bitset->reserve(TABLE_LENGTH);
}

void Scan::int_eq(const uint32_t id, const uint32_t value) {
  const auto& column = _table->get_int_column(id);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (column[i] == value) result_ref.push_back(i);
  }
}

void Scan::int_leq(uint32_t id, uint32_t value) {
    const auto& column = _table->get_int_column(id);

    auto& result_ref = *_result;

    for (uint32_t i = 0; i < column.size(); i++) {
        if (column[i] <= value) result_ref.push_back(i);
    }
}

void Scan::int_eq_bitset(const uint32_t id, const uint32_t value) {
  const auto& column = _table->get_int_column(id);

  auto& result_ref = *_result_bitset;
  result_ref.resize(std::distance(column.cbegin(), column.cend()));

  for (uint32_t i = 0; i < column.size(); i++) {
      result_ref[i] =  (column[i] == value);
  }
}

void Scan::int_leq_bitset(const uint32_t id, const uint32_t value) {
    const auto& column = _table->get_int_column(id);

    auto& result_ref = *_result_bitset;
    result_ref.resize(std::distance(column.cbegin(), column.cend()));

    for (uint32_t i = 0; i < column.size(); i++) {
        result_ref[i] = (column[i] <= value);
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

void Scan::int_leq_dict(const uint32_t id, const uint32_t value) {
    const auto& dict = _table->get_int_dictionary(id);
    const auto& av = _table->get_int_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result;

    for (uint32_t i = 0; i  < av.size(); i++) {
        if (av[i] <= distance) result_ref.push_back(i);
    }
}

void Scan::int_eq_dict_bitset(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& av = _table->get_int_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset;
    result_ref.resize(std::distance(av.cbegin(), av.cend()));

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref[i] = (av[i] == distance);
  }
}

void Scan::int_leq_dict_bitset(const uint32_t id, const uint32_t value) {
    const auto& dict = _table->get_int_dictionary(id);
    const auto& av = _table->get_int_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result_bitset;
    result_ref.resize(std::distance(av.cbegin(), av.cend()));

    for (uint32_t i = 0; i  < av.size(); i++) {
        result_ref[i] = (av[i] <= distance);
    }
}

void Scan::int_eq_index(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& offsets = _table->get_int_offset(id);
  const auto& indizes = _table->get_int_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  const auto& index_begin = indizes.cbegin() + offsets[distance];
  const auto& index_end = indizes.cbegin() + offsets[distance+1];

  result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

void Scan::int_eq_index_bitset(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& offsets = _table->get_int_offset(id);
  const auto& indizes = _table->get_int_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset_init;

  auto it = indizes.begin() + offsets[distance];
  const auto& index_end = indizes.cbegin() + offsets[distance+1];

  for (; it != index_end; ++it) {
    result_ref[*it] = true;
  }
}

void Scan::int_leq_index(const uint32_t id, const uint32_t value) {
    const auto& dict = _table->get_int_dictionary(id);
    const auto& offsets = _table->get_int_offset(id);
    const auto& indizes = _table->get_int_indizes(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result;

    const auto& index_begin = indizes.cbegin();
    const auto& index_end = indizes.cbegin() + offsets[distance+1];

    result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

void Scan::int_leq_index_bitset(const uint32_t id, const uint32_t value) {
  const auto& dict = _table->get_int_dictionary(id);
  const auto& offsets = _table->get_int_offset(id);
  const auto& indizes = _table->get_int_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset_init;

  auto it = indizes.begin();
  const auto& index_end = indizes.cbegin() + offsets[distance+1];

  for (; it != index_end; ++it) {
    result_ref[*it] = true;
  }
}

void Scan::int_eq_tree(const uint32_t id, const uint32_t value) {
    const auto& tree = _table->get_int_tree(id);
    const auto results = tree.equal_range(value);
    auto& result_ref = *_result;

    for (auto it=results.first; it!=results.second; it.increment()) {
        result_ref.push_back((*it).second);
    }

}

void Scan::int_leq_tree(const uint32_t id, const uint32_t value) {
    const auto& tree = _table->get_int_tree(id);
    const auto results = tree.equal_range(value);
    auto& result_ref = *_result;

    for (auto it=tree.begin(); it!=results.second; it.increment()) {
        result_ref.push_back((*it).second);
    }

}

void Scan::string_eq(const uint32_t id, const String& value) {
  const auto& column = _table->get_string_column(id);

  auto& result_ref = *_result;

  for (uint32_t i = 0; i < column.size(); i++) {
    if (column[i] == value) result_ref.push_back(i);
  }
}

void Scan::string_leq(const uint32_t id, const String& value) {
    const auto& column = _table->get_string_column(id);

    auto& result_ref = *_result;

    for (uint32_t i = 0; i < column.size(); i++) {
        if (column[i] <= value) result_ref.push_back(i);
    }
}


void Scan::string_eq_bitset(const uint32_t id, const String& value) {
    const auto is_equal = [](const String& a, const String& b) {
        return a[0] == b[0] & a[1] == b[1] & a[2] == b[2] & a[3] == b[3] & a[4] == b[4] &
               a[5] == b[5] & a[6] == b[6] & a[7] == b[7] & a[8] == b[8] & a[9] == b[9];
    };
  const auto& column = _table->get_string_column(id);

  auto& result_ref = *_result_bitset;
  result_ref.resize(std::distance(column.cbegin(), column.cend()));

  for (uint32_t i = 0; i < column.size(); i++) {
    result_ref[i] = is_equal(column[i], value);
  }
}

void Scan::string_leq_bitset(const uint32_t id, const String& value) {
    const auto& column = _table->get_string_column(id);

    auto& result_ref = *_result_bitset;
    result_ref.resize(std::distance(column.cbegin(), column.cend()));

    for (uint32_t i = 0; i < column.size(); i++) {
        result_ref[i] = (column[i] <= value);
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

void Scan::string_leq_dict(const uint32_t id, const String& value) {
    const auto& dict = _table->get_string_dictionary(id);
    const auto& av = _table->get_string_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result;

    for (uint32_t i = 0; i  < av.size(); i++) {
        if (av[i] <= distance) result_ref.push_back(i);
    }
}


void Scan::string_eq_dict_bitset(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& av = _table->get_string_attribute_vector(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset;
  result_ref.resize(std::distance(av.cbegin(), av.cend()));

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref[i] = (av[i] == distance);
  }
}

void Scan::string_leq_dict_bitset(const uint32_t id, const String& value) {
    const auto& dict = _table->get_string_dictionary(id);
    const auto& av = _table->get_string_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result_bitset;
    result_ref.resize(std::distance(av.cbegin(), av.cend()));

    for (uint32_t i = 0; i  < av.size(); i++) {
        result_ref[i] = (av[i] <= distance);
    }
}

void Scan::string_eq_index(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& offsets = _table->get_string_offset(id);
  const auto& indizes = _table->get_string_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result;

  const auto& index_begin = indizes.cbegin() + offsets[distance];
  const auto& index_end = indizes.cbegin() + offsets[distance+1];
//TODO resize, dann direktzugriff
//TODO memcopy, billoschleife, index mit bitset mergen und plotten
  result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

void Scan::string_eq_index_bitset(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& offsets = _table->get_string_offset(id);
  const auto& indizes = _table->get_string_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset_init;

  auto it = indizes.begin() + offsets[distance];
  const auto& index_end = indizes.cbegin() + offsets[distance+1];

  for (; it != index_end; ++it) {
    result_ref[*it] = true;
  }
}

void Scan::string_leq_index(const uint32_t id, const String& value) {
    const auto& dict = _table->get_string_dictionary(id);
    const auto& offsets = _table->get_string_offset(id);
    const auto& indizes = _table->get_string_indizes(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result;

    const auto& index_begin = indizes.cbegin();
    const auto& index_end = indizes.cbegin() + offsets[distance+1];

    result_ref.insert(result_ref.cbegin(), index_begin, index_end);
}

void Scan::string_leq_index_bitset(const uint32_t id, const String& value) {
  const auto& dict = _table->get_string_dictionary(id);
  const auto& offsets = _table->get_string_offset(id);
  const auto& indizes = _table->get_string_indizes(id);

  const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
  const auto distance = std::distance(dict.cbegin(), lower_bound);

  auto& result_ref = *_result_bitset_init;

  auto it = indizes.begin();
  const auto& index_end = indizes.cbegin() + offsets[distance+1];

  for (; it != index_end; ++it) {
    result_ref[*it] = true;
  }
}

void Scan::string_eq_tree(const uint32_t id, const String& value) {
    const auto& tree = _table->get_string_tree(id);
    const auto& results = tree.equal_range(value);
    auto& result_ref = *_result;

    for (auto it=results.first; it!=results.second; it.increment()) {
        result_ref.push_back((*it).second);
    }
}

void Scan::string_leq_tree(const uint32_t id, const String& value) {
    const auto& tree = _table->get_string_tree(id);
    const auto& results = tree.equal_range(value);
    auto& result_ref = *_result;

    for (auto it=tree.begin(); it != results.second; it.increment()) {
        result_ref.push_back((*it).second);
    }
}

const std::shared_ptr<std::vector<uint8_t >> Scan::get_result_bitset() {
  if (std::find(_result_bitset_init->cbegin(), _result_bitset_init->cend(), true) != _result_bitset_init->cend()) {
    return _result_bitset_init;
  } else {
    return _result_bitset;
  }
}

}  // namespace indexvsscan
