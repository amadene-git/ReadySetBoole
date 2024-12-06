#include <iostream>
#include <cstdint>
#include <bitset>
#include <limits>

uint32_t gray_code(uint32_t n)
{
	int ret = 0;

	for (int i = 0; 1 << i <= n; i++)
		if (((n >> i) & 1) ^ ((n >> (i + 1)) & 1))
			ret = ret | (1 << i);
	return (ret);
}

int main()
{

	for (int i = 0; i <= 16; ++i)
	{
		// std::cout << i << ".\n"
		// 					<< "normal " << std::bitset<8>(i) << std::endl;
		std::cout << "gray   "<< std::bitset<8>(gray_code(i)) << std::endl
							<< std::endl;
	}
	std::cout << "max 	"<< std::bitset<32>(std::numeric_limits<uint32_t>::max()) << std::endl;
}