#include "multiplier.h"

uint32_t multiplier(uint32_t a, uint32_t b) {
  uint32_t tmp;

  if (a > b) {
    tmp = a;
    a = b;
    b = tmp;
  }
  tmp = 0;
  for (uint32_t i = 0; (uint32_t(1) << i) <= a; i++)
    if (((a >> i) & 1) == 1) {
      tmp = adder(tmp, b << i);
      if (tmp < b) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << "():";
        throw std::overflow_error(oss.str());
      }
    }
  return (tmp);
}