#include <00_Adder/adder.h>

uint32_t adder(uint32_t a, uint32_t b) {
  uint32_t ret = 0;
  uint32_t result = 0;

  for (int i = 0; i < 32; i++) {
    if ((((a & b & ret) >> i) & 1) == 1)  // 1 + 1 + 1
    {
      result = result | (1 << i);
      ret = ret | (1 << (i + 1));
    } else if ((((a ^ b ^ ret) >> i) & 1) == 1)  // 0 + 0 + 1
      result = result | (1 << i);
    else if ((((a | b | ret) >> i) & 1) == 1)  // 1 + 1 + 0
      ret = ret | (1 << (i + 1));
  }

  if ((result < a) | (result < b)) {
    throw std::overflow_error("adder() overflow");
  }
  return (result);
}

/*
 0 + 0 + 0 = 00
 1 + 0 + 0 = 01
 1 + 1 + 0 = 10 (on pose 0 et on retient 1)
 1 + 1 + 1 = 11 (on pose 1 et on retient 1)

exemple

      1 1      ret
      1 0 1    a
 +    1 1 1    b
 ------------
 =  1 1 0 0    result
*/
