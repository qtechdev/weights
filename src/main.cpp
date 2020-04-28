#include <type_traits>
#include <iostream>

#include "conv.hpp"

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

enum class error_codes {
  not_enough_args = 1,
  invalid_unit = 100,
  invalid_weight = 101
};

enum class units {
  kilograms,
  pounds,
  invalid
};

void show_usage(const std::string name) {
  std::cout << "usage: " << name << " " << "<-l/-k> <weight>\n";
}

units parse_unit(const std::string unit) {
  if (unit.length() != 2) {
    return units::invalid;
  }

  if (unit.compare(0, 1, "-") != 0) {
    return units::invalid;
  }

  if (unit.compare(1, 1, "k") == 0) {
    return units::kilograms;
  } else if (unit.compare(1, 1, "l") == 0) {
    return units::pounds;
  }

  return units::invalid;
}

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    show_usage(argv[0]);
    return to_underlying(error_codes::not_enough_args);
  }

  units unit = parse_unit(argv[1]);
  char *end;
  double weight = std::strtod(argv[2], &end);

  if (*end != '\0') {
    std::cout << "invalid weight\n";
    return to_underlying(error_codes::invalid_weight);
  }

  switch (unit) {
    case units::kilograms:
      std::cout << weight << " kg is equal to " << kg_to_lb(weight) << " lb\n";
      break;
    case units::pounds:
      std::cout << weight << " lb is equal to " << lb_to_kg(weight) << " kg\n";
      break;
    case units::invalid: // fallthrough
    default:
      std::cout << "invalid unit\n";
      return to_underlying(error_codes::invalid_unit);
  }

  return 0;
}
