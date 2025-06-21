#include <iostream>
#include <cstdint>
#include <bitset>
#include <limits>

uint32_t gray_code(uint32_t n)
{
	int ret = 0;

	for (size_t i = 0; static_cast<uint32_t>(1 << i) <= n; i++)
		if (((n >> i) & 1) ^ ((n >> (i + 1)) & 1))
			ret = ret | (1 << i);
	return (ret);
}

int main()
{

	for (int i = 0; i <= 16; ++i)
	{
		std::cout << i << ".\n"
				  << "normal " << std::bitset<8>(i) << std::endl;
		std::cout << "gray   " << std::bitset<8>(gray_code(i)) << std::endl
				  << std::endl;
	}
}