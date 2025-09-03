#include <02_GrayCode/grayCode.h>

uint32_t gray_code(uint32_t n) {
  int ret = 0;

  for (size_t i = 0; static_cast<uint32_t>(1 << i) <= n; i++)
    if (((n >> i) & 1) ^ ((n >> (i + 1)) & 1))
      ret = ret | (1 << i);
  return (ret);
}