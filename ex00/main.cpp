#include "adder.h"
#include <limits>

int main()
{
	if (adder(0, 0) != 0)
		throw std::runtime_error("0 + 0 Error");

	try
	{
		uint32_t a;
		uint32_t b;
		uint32_t c;
		srand(time(NULL));

		for (int i = 0; i < 200 && i >= 0; i++)
		{
			c = (uint32_t)rand() % 2147483648;
			b = (uint32_t)rand() % 2147483648;
			a = c % b;
			b = b % c;

			c = adder(a, b);
			std::cout << i << ".  " << a << " + " << b << " = " << c << std::endl;
			if (c != a + b)
				throw std::runtime_error(std::to_string(a) + " + " + std::to_string(b) + " != " + std::to_string(c));
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		uint32_t max = std::numeric_limits<uint32_t>::max();

		adder(1, max);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}