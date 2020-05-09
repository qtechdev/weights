#include "conv.hpp"



// from kg
pound_t kg_to_lb(const kilogram_t kg) {
  return kg.values[0] * 2.20462262185;
}
stone_t kg_to_st(const kilogram_t kg) {
  return kg.values[0] * (2.20462262185 / 14.0);
}

// from lb
kilogram_t lb_to_kg(const pound_t lb) {
  return lb.values[0] * 0.45359237;
}
stone_t lb_to_st(const pound_t lb) {
  return lb.values[0] / 14;
}

// from st
kilogram_t st_to_kg(const stone_t st) {
  return (st.values[0] * 14 + st.values[1]) * 0.45359237;
}
pound_t st_to_lb(const stone_t st) {
  return st.values[0] * 14 + st.values[1];
}
