#include <iostream>

#include "units.hpp"

std::ostream& operator<<(std::ostream &os, const unit_t &u) {
  switch (u) {
    case unit_t::kilograms: os << "kilograms"; break;
    case unit_t::pounds: os << "pounds"; break;
    case unit_t::stone: os << "stone"; break;
    default: os << "invalid unit"; break;
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

std::ostream &operator<<(std::ostream &os, const weight_t &w) {
  for (int i = 0; i < w.count; i++) {
    os << w.values[i] << " " << w.units[i];

    if (i != w.count) {
      os << " ";
    }

  }
  return os;
}

kilogram_t::kilogram_t(const double kg) {
  values.push_back(kg);
  units.push_back("kg");
}

pound_t::pound_t(const double lb) {
  values.push_back(lb);
  units.push_back("lb");
}

stone_t::stone_t(const double st) {
  count = 2;
  int x = st;
  values.push_back(x);
  values.push_back((st - x) * 14);
  units.push_back("st");
  units.push_back("lb");
}
stone_t::stone_t(const int st, const double lb) {
  count = 2;
  values.push_back(st);
  values.push_back(lb);
  units.push_back("st");
  units.push_back("lb");
}
