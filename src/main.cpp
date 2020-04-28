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
  invalid_weight = 101
};

enum class unit_t {
  kilograms,
  pounds,
  invalid
};

void show_usage(const std::string name) {
  std::cout << "usage: " << name << " " << "<unit> <weight>\n";
}

int main(int argc, char *argv[]) {
  const flags::args args(argc, argv);

  bool unit_ok = false;
  unit_t unit = unit_t::invalid;

  const auto kilograms = args.get<double>("k");
  if (kilograms) {
    unit_ok = true;
    unit = unit_t::kilograms;
    std::cout << "kilograms: " << *kilograms << std::endl;
    std::cout << *kilograms << " kg is equal to " << kg_to_lb(*kilograms) << " lb\n";
    return 0;
  }

  const auto pounds = args.get<double>("l");
  if (pounds) {
    unit_ok = true;
    unit = unit_t::pounds;
    std::cout << "pounds: " << *pounds << std::endl;
    std::cout << *pounds << " lb is equal to " << lb_to_kg(*pounds) << " kg\n";
    return 0;
  }

  if (!unit_ok) {
    std::cerr << "invalid unit" << std::endl;
    return to_underlying(error_code_t::invalid_unit);
  }


  return 0;
}
