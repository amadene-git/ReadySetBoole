#define BOOST_TEST_MODULE EXERCICE_02_GRAY_CODE
#include <boost/test/included/unit_test.hpp>

#include <02_GrayCode/grayCode.h>

BOOST_AUTO_TEST_CASE(basic_test)
{
	for (int i = 0; i <= 16; ++i)
	{
		std::cout << i << ".\n"
				  << "normal " << std::bitset<8>(i) << std::endl;
		std::cout << "gray   " << std::bitset<8>(gray_code(i)) << std::endl
				  << std::endl;
	}
}
