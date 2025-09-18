#include <02_GrayCode/grayCode.h>

uint32_t gray_code(uint32_t n) {
  return n ^ (n >> 1);
}

// uint32_t gray_code(uint32_t n) {
//   int ret = 0;

//   for (uint32_t i = 0; (1 << i) <= n; i++) {
//     if (((n >> i) & 1) ^ ((n >> (i + 1)) & 1)) {
//       ret = ret | (1 << i);
//     }
//   }
//   return (ret);
// }