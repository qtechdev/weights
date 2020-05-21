#ifndef __MESSAGES_HPP__
#define __MESSAGES_HPP__
#include <string>

struct Messages {
  std::string usage;
  std::string not_enough_args;
  std::string too_many_args;
  std::string invalid_unit;
  std::string invalid_weight;
  std::string same_unit;
  std::string is_equal_to;
  std::string kg_full;
  std::string lb_full;
  std::string st_full;
  std::string kg_abbr;
  std::string lb_abbr;
  std::string st_abbr;
};

struct en : Messages {
  en() {
    usage = "usage: \n\t%1$s -f <unit> -t <unit> -w <weight> \n\t%1$s -h";
    not_enough_args = "Missing args.";
    too_many_args = "Please quote weights with multiple units.";
    invalid_unit = "Invalid unit.";
    invalid_weight = "Invalid weight.";
    same_unit = "Please specify two different units...";
    is_equal_to = " is approximately equal to ";
    kg_full = "kilograms";
    lb_full = "pounds";
    st_full = "stone";
    kg_abbr = "kg";
    lb_abbr = "lb";
    st_abbr = "st";
  }
};

#endif /* end of include guard: __MESSAGES_HPP__ */
