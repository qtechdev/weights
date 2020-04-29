#include <type_traits>
#include <iostream>

#include "conv.hpp"
#include "flags.h" // https://github.com/sailormoon/flags

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

enum class error_code_t {
  not_enough_args = 1,
  invalid_unit = 100,
  invalid_weight = 101,
  same_unit = 102,
};

enum class unit_t {
  kilograms,
  pounds,
  invalid
};

std::ostream& operator<<(std::ostream &os, const unit_t &u) {
  switch (u) {
    case unit_t::kilograms: os << "kilograms"; break;
    case unit_t::pounds: os << "pounds"; break;
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
    default: u = unit_t::invalid; break;
  }

  return stream;
}

void show_usage(const std::string name) {
  std::cout << "usage: " << name << " <-f unit> <-w weight> <-t unit>\n";
}

int main(int argc, char *argv[]) {
  const flags::args args(argc, argv);

  const auto unit_1 = args.get<unit_t>("f");
  const auto weight = args.get<double>("w");
  const auto unit_2 = args.get<unit_t>("t");

  if (!weight) {
    show_usage(argv[0]);
    return to_underlying(error_code_t::invalid_weight);
  }

  if (!unit_1 || !unit_2) {
    show_usage(argv[0]);
    return to_underlying(error_code_t::invalid_unit);
  }

  if (unit_1 == unit_2) {
    std::cerr << "Please specify two different units..." << std::endl;
    return to_underlying(error_code_t::same_unit);
  }

  double new_weight = 0;

  switch (*unit_1) {
    case unit_t::kilograms:
      switch (*unit_2) {
        case unit_t::pounds: new_weight = kg_to_lb(*weight); break;
      };
      break;

    case unit_t::pounds:
      switch (*unit_2) {
        case unit_t::kilograms: new_weight = lb_to_kg(*weight); break;
      };
      break;
  }

  std::cout << *weight << " " << *unit_1 << " is approcimately equal to ";
  std::cout << new_weight << " " << *unit_2 << std::endl;

  return 0;
}
