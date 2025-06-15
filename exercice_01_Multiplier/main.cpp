#include "multiplier.h"
#include <limits>

int main()
{
	try
	{
		uint32_t a;
		uint32_t b;
		uint32_t c;
		srand(time(NULL));

		for (int i = 0; i < 200 && i >= 0; i++)
		{
			a = (uint32_t)rand() % 10000;
			b = (uint32_t)rand() % 10000;
			c = multiplier(a, b);

			std::cout << i << ".  " << a << " * " << b << " = " << c << std::endl;
			if (c != a * b)
				throw std::runtime_error(std::to_string(a) + " * " + std::to_string(b) + " != " + std::to_string(c));
		}

		std::cout << multiplier(0, 0) << " = 0" << std::endl;
		std::cout << multiplier(0, 1) << " = 0" << std::endl;
		std::cout << multiplier(12, 0) << " = 0" << std::endl;
		std::cout << multiplier(2, 2147483647) << "= " << std::numeric_limits<uint32_t>::max() - 1 << std::endl;
		std::cout << multiplier(787878787, 878787878) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}