#include "conv.hpp"

// from kg
double kg_to_lb(const double kg) {
  return kg * 2.20462262185;
}
double kg_to_st(const double kg) {
  return kg * (2.20462262185 / 14.0);
}

// from lb
double lb_to_kg(const double lb) {
  return lb * 0.45359237;
}
double lb_to_st(const double lb) {
  return lb / 14;
}

// from st
double st_to_kg(const double st) {
  return st / (2.20462262185 / 14.0);
}
double st_to_lb(const double st) {
  return st * 14;
}
