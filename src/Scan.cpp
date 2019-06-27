#include "Scan.hpp"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <iostream>
#include <math.h>

namespace indexvsscan {

Scan::Scan(const std::shared_ptr<Table> table) : _table(table),
                                                 _result(std::make_shared<std::vector<uint32_t>>()),
                                                 _result_bitset(std::make_shared<std::vector<char>>()),
                                                 _result_bitset_init(std::make_shared<std::vector<char>>(table->num_rows)){
  _result->reserve(table->num_rows);
  _result_bitset->reserve(table->num_rows);
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

  for (uint32_t i = 0; i < column.size(); i++) {
    result_ref.push_back(column[i] == value);
  }
}

void Scan::int_leq_bitset(const uint32_t id, const uint32_t value) {
    const auto& column = _table->get_int_column(id);

    auto& result_ref = *_result_bitset;

    for (uint32_t i = 0; i < column.size(); i++) {
        result_ref.push_back(column[i] <= value);
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

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref.push_back(av[i] == distance);
  }
}

void Scan::int_leq_dict_bitset(const uint32_t id, const uint32_t value) {
    const auto& dict = _table->get_int_dictionary(id);
    const auto& av = _table->get_int_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result_bitset_init;

    for (uint32_t i = 0; i  < av.size(); i++) {
        result_ref[i] = av[i] <= distance;
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
  const auto& column = _table->get_string_column(id);

  auto& result_ref = *_result_bitset;

  for (uint32_t i = 0; i < column.size(); i++) {
    result_ref.push_back(column[i] == value);
  }
}

void Scan::string_leq_bitset(const uint32_t id, const String& value) {
    const auto& column = _table->get_string_column(id);

    auto& result_ref = *_result_bitset_init;

    for (uint32_t i = 0; i < column.size(); i++) {
        result_ref[i] = column[i] <= value;
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

  for (uint32_t i = 0; i  < av.size(); i++) {
    result_ref.push_back(av[i] == distance);
  }
}

void Scan::string_leq_dict_bitset(const uint32_t id, const String& value) {
    const auto& dict = _table->get_string_dictionary(id);
    const auto& av = _table->get_string_attribute_vector(id);

    const auto lower_bound = std::lower_bound(dict.cbegin(), dict.cend(), value);
    const auto distance = std::distance(dict.cbegin(), lower_bound);

    auto& result_ref = *_result_bitset_init;

    for (uint32_t i = 0; i  < av.size(); i++) {
        result_ref[i] = av[i] <= distance;
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

const std::shared_ptr<std::vector<char>> Scan::get_result_bitset() {
  if (std::find(_result_bitset_init->cbegin(), _result_bitset_init->cend(),
                static_cast<char>(true)) != _result_bitset_init->cend()) {
    return _result_bitset_init;
  } else {
    return _result_bitset;
  }
}

}  // namespace indexvsscan
