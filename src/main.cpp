#include <iostream>
#include <optional>
#include <type_traits>

#include "conv.hpp"
#include "units.hpp"
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

void show_usage(const std::string name) {
  std::cout << "usage: " << name << " <-f unit> <-w weight> <-t unit>\n";
}

std::optional<weight_t> f(std::optional<unit_t> u, std::optional<double> w) {
  if (!u || !w) {
    return std::nullopt;
  }

  switch (*u) {
    case unit_t::kilograms: return kilogram_t(*w);
    case unit_t::pounds: return pound_t(*w);
    case unit_t::stone: return stone_t(*w);
  }

  return std::nullopt;
}

int main(int argc, char *argv[]) {
  const flags::args args(argc, argv);

  const auto help = args.get<bool>("h") || args.get<bool>("help");

  if (help) {
    show_usage(argv[0]);
    return 0;
  }

  const auto unit_1 = args.get<unit_t>("f");
  const auto weight = args.get<double>("w");
  const auto unit_2 = args.get<unit_t>("t");

  if (!weight || !unit_1 || !unit_2) {
    show_usage(argv[0]);
    return to_underlying(error_code_t::not_enough_args);

  }

  if (!weight) {
    std::cerr << "invalid weight" << std::endl;
    return to_underlying(error_code_t::invalid_weight);
  }

  if (!unit_1 || !unit_2) {
    std::cerr << "invalid unit" << std::endl;
    return to_underlying(error_code_t::invalid_unit);
  }

  if (unit_1 == unit_2) {
    std::cerr << "Please specify two different units..." << std::endl;
    return to_underlying(error_code_t::same_unit);
  }

  const auto weight_1 = f(unit_1, weight);
  weight_t weight_2;

  switch (*unit_1) {
    case unit_t::kilograms:
      switch (*unit_2) {
        case unit_t::pounds: weight_2 = kg_to_lb(*weight); break;
        case unit_t::stone: weight_2 = kg_to_st(*weight); break;
      };
      break;
    case unit_t::pounds:
      switch (*unit_2) {
        case unit_t::kilograms: weight_2 = lb_to_kg(*weight); break;
        case unit_t::stone: weight_2 = lb_to_st(*weight); break;
      };
      break;
    case unit_t::stone:
      switch (*unit_2) {
        case unit_t::kilograms: weight_2 = st_to_kg(*weight); break;
        case unit_t::pounds: weight_2 = st_to_lb(*weight); break;
      };
      break;
  }

  std::cout << *weight_1 << " is approximately equal to " << weight_2;
  std::cout << std::endl;

  return 0;
}
