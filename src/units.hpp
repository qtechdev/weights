#ifndef __UNITS_HPP__
#define __UNITS_HPP__
#include <iostream>
#include <string>
#include <vector>

enum class unit_t {
  kilograms,
  pounds,
  stone,
  invalid
};
std::ostream& operator<<(std::ostream &os, const unit_t &u);
std::istream& operator>>(std::istream &stream, unit_t &u);

struct weight_t {
  int count = 1;
  std::vector<double> values;
  std::vector<std::string> units;
};
std::ostream& operator<<(std::ostream &os, const weight_t &u);

struct kilogram_t : public weight_t {
  kilogram_t(const double kg);
};
struct pound_t : public weight_t {
  pound_t(const double lb);
};
struct stone_t : public weight_t {
  stone_t(const double st);
  stone_t(const int st, const double lb);
};

#endif // __UNITS_HPP__
