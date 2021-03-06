#include <iostream>
#include <cstdio>
#include <optional>
#include <type_traits>
#include "text.hpp"

#include "conv.hpp"
#include "units.hpp"
#include "flags.h" // https://github.com/sailormoon/flags

Messages msg = en();

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

enum class error_code_t {
  not_enough_args = 1,
  too_many_args = 2,
  invalid_unit = 100,
  invalid_weight = 101,
  same_unit = 102,
};

void show_usage(const std::string name) {
  char buf[100];
  int n = std::snprintf(buf, 100, msg.usage.c_str(), name.c_str());
  std::snprintf(buf+n, 100-n, "\n");
  std::cerr << buf;
}

std::istream &operator>>(std::istream &stream, weight_t &w) {
  double d;
  while (stream >> d) {
    w.values.push_back(d);
  }

  if (w.values.size() >= 1) {
    stream.clear();
  }

  return stream;
}

int main(int argc, char *argv[]) {
  const flags::args args(argc, argv);

  const auto help = args.get<bool>("h") || args.get<bool>("help");

  if (help) {
    show_usage(argv[0]);
    return 0;
  }

  const auto _unit_1 = args.get<unit_t>("f");
  const auto _weight = args.get<weight_t>("w");
  const auto _unit_2 = args.get<unit_t>("t");
  const auto &positional = args.positional();

  if (!(_weight && _unit_1 && _unit_2)) {
    char buf[100];
    int n = std::snprintf(buf, 100, msg.not_enough_args.c_str());
    std::snprintf(buf+n, 100-n, "\n");
    std::cerr << buf;
    return to_underlying(error_code_t::not_enough_args);
  }

  if (!_weight) {
    char buf[100];
    int n = std::snprintf(buf, 100, msg.invalid_weight.c_str());
    std::snprintf(buf+n, 100-n, "\n");
    std::cerr << buf;
    return to_underlying(error_code_t::invalid_weight);
  }

  if (!_unit_1 || !_unit_2) {
    char buf[100];
    int n = std::snprintf(buf, 100, msg.invalid_unit.c_str());
    std::snprintf(buf+n, 100-n, "\n");
    std::cerr << buf;
    return to_underlying(error_code_t::invalid_unit);
  }

  if (_unit_1 == _unit_2) {
    char buf[100];
    int n = std::snprintf(buf, 100, msg.same_unit.c_str());
    std::snprintf(buf+n, 100-n, "\n");
    std::cerr << buf;
    return to_underlying(error_code_t::same_unit);
  }

  if (positional.size() > 0) {
    char buf[100];
    int n = std::snprintf(buf, 100, msg.too_many_args.c_str());
    std::snprintf(buf+n, 100-n, "\n");
    std::cerr << buf;
    return to_underlying(error_code_t::too_many_args);
  }

  weight_t weight = *_weight;
  weight.unit = *_unit_1;

  std::cout << weight << msg.is_equal_to;
  switch (*_unit_2) {
    case unit_t::kilograms: std::cout << kilogram_t(weight); break;
    case unit_t::pounds: std::cout << pound_t(weight); break;
    case unit_t::stone: std::cout << stone_t(weight); break;
    case unit_t::invalid:
    default: std::cout << "[invalid unit]"; break;
  }
  std::cout << std::endl;

  return 0;
}
