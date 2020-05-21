#include <iostream>
#include <vector>

#include "conv.hpp"
#include "text.hpp"

#include "units.hpp"

extern Messages msg;

std::ostream& operator<<(std::ostream &os, const unit_t &u) {
  switch (u) {
    case unit_t::kilograms: os << msg.kg_full; break;
    case unit_t::pounds: os << msg.lb_full; break;
    case unit_t::stone: os << msg.st_full; break;
    default: os << msg.invalid_unit; break;
  }

  return os;
}

std::istream& operator>>(std::istream &stream, unit_t &u) {
  char unit;
  stream >> unit;

  switch (unit) {
    case 'k': u = unit_t::kilograms; break;
    case 'l': u = unit_t::pounds; break;
    case 's': u = unit_t::stone; break;
    default: u = unit_t::invalid; stream.setstate(std::ios::failbit); break;
  }

  return stream;
}

weight_t::weight_t(const std::vector<double> v, const unit_t &u) {
  values = v;
  unit = u;
}

std::ostream &operator<<(std::ostream &os, const weight_t &w) {
  std::vector<std::string> units;
  switch (w.unit) {
    case unit_t::kilograms: units = {msg.kg_abbr}; break;
    case unit_t::pounds: units = {msg.lb_abbr}; break;
    case unit_t::stone: units = {msg.st_abbr, msg.lb_abbr}; break;
    default: units = {msg.invalid_unit}; break;
  }
  int count = units.size();

  for (int i = 0; i < count; i++) {
    os << w.values[i] << " " << units[i];

    if (i != (count - 1)) {
      os << " ";
    }

  }
  return os;
}

/* kilogram_t ****************************************************************/
kilogram_t::kilogram_t(const double kg) {
  values.push_back(kg);
  unit = unit_t::kilograms;
}

kilogram_t::kilogram_t(const std::vector<double> &vec) {
  values = vec;
  unit = unit_t::kilograms;
}

kilogram_t::kilogram_t(const weight_t &w) {
  switch (w.unit) {
    case unit_t::kilograms: *this = kilogram_t(w.values); break;
    case unit_t::pounds: *this = pound_t(w.values); break;
    case unit_t::stone: *this = stone_t(w.values); break;
    default: values = {0}; unit = unit_t::invalid; break;
  }
}

kilogram_t::kilogram_t(const pound_t &lb) {
  *this = lb_to_kg(lb);
}
kilogram_t::kilogram_t(const stone_t &st) {
  *this = st_to_kg(st);
}

/* pound_t *******************************************************************/
pound_t::pound_t(const double lb) {
  values.push_back(lb);
  unit = unit_t::pounds;
}

pound_t::pound_t(const std::vector<double> &vec) {
  values = vec;
  unit = unit_t::pounds;
}

pound_t::pound_t(const weight_t &w) {
  switch (w.unit) {
    case unit_t::kilograms: *this = kilogram_t(w.values); break;
    case unit_t::pounds: *this = pound_t(w.values); break;
    case unit_t::stone: *this = stone_t(w.values); break;
    default: values = {0}; unit = unit_t::invalid; break;
  }
}

pound_t::pound_t(const kilogram_t &kg) {
  *this = kg_to_lb(kg);
}
pound_t::pound_t(const stone_t &st) {
  *this = st_to_lb(st);
}

/* stone_t *******************************************************************/
stone_t::stone_t(const double st) {
  int x = st;
  values.push_back(x);
  values.push_back((st - x) * 14);
  unit = unit_t::stone;
}

stone_t::stone_t(const int st, const double lb) {
  values.push_back(st);
  values.push_back(lb);
  unit = unit_t::stone;
}

stone_t::stone_t(const std::vector<double> &vec) {
  values = vec;
  unit = unit_t::stone;
}

stone_t::stone_t(const weight_t &w) {
  switch (w.unit) {
    case unit_t::kilograms: *this = kilogram_t(w.values); break;
    case unit_t::pounds: *this = pound_t(w.values); break;
    case unit_t::stone: *this = stone_t(w.values); break;
    default: values = {0}; unit = unit_t::invalid; break;
  }
}

stone_t::stone_t(const kilogram_t &kg) {
  *this = kg_to_st(kg);
}
stone_t::stone_t(const pound_t &lb) {
  *this = lb_to_st(lb);
}
