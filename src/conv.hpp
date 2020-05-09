#ifndef __CONV_HPP__
#define __CONV_HPP__

#include "units.hpp"

pound_t kg_to_lb(const kilogram_t kg);
stone_t kg_to_st(const kilogram_t kg);

kilogram_t lb_to_kg(const pound_t lb);
stone_t lb_to_st(const pound_t lb);

kilogram_t st_to_kg(const stone_t st);
pound_t st_to_lb(const stone_t st);

#endif // __CONV_HPP__
