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

struct weight_t;
struct kilogram_t;
struct pound_t;
struct stone_t;

struct weight_t {
  weight_t() = default;
  weight_t(const std::vector<double> w, const unit_t &u);

  std::vector<double> values;
  unit_t unit;
};
std::ostream& operator<<(std::ostream &os, const weight_t &u);

struct kilogram_t : public weight_t {
  kilogram_t(const double kg);
  kilogram_t(const std::vector<double> &vec);
  kilogram_t(const weight_t &w);
  kilogram_t(const pound_t &lb);
  kilogram_t(const stone_t &st);
};
struct pound_t : public weight_t {
  pound_t(const double lb);
  pound_t(const std::vector<double> &vec);
  pound_t(const weight_t &w);
  pound_t(const kilogram_t &lb);
  pound_t(const stone_t &st);
};
struct stone_t : public weight_t {
  stone_t(const double st);
  stone_t(const int st, const double lb);
  stone_t(const std::vector<double> &vec);
  stone_t(const weight_t &w);
  stone_t(const kilogram_t &lb);
  stone_t(const pound_t &st);
};

#endif // __UNITS_HPP__
