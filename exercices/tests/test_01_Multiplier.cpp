#define BOOST_TEST_MODULE EXERCICE_01_MULTIPLIER
#include <boost/test/included/unit_test.hpp>

#include <01_Multiplier/multiplier.h>
#include <limits>

BOOST_AUTO_TEST_CASE(basic_test)
{
	BOOST_CHECK_EQUAL(multiplier(6, 7), 42);
	BOOST_CHECK_EQUAL(multiplier(0, 0), 0);
	BOOST_CHECK_EQUAL(multiplier(0, 1), 0);
	BOOST_CHECK_EQUAL(multiplier(12, 0), 0);
	BOOST_CHECK_EQUAL(multiplier(2, 2147483647), std::numeric_limits<uint32_t>::max() - 1);
}

BOOST_AUTO_TEST_CASE(loop_test)
{
	srand(time(NULL));

	for (int i = 0; i < 200 && i >= 0; i++)
	{
		uint32_t a = (uint32_t)rand() % 10000;
		uint32_t b = (uint32_t)rand() % 10000;
		BOOST_CHECK_EQUAL(multiplier(a, b), a * b);
	}
}

BOOST_AUTO_TEST_CASE(overflow_test)
{
	try
	{
		multiplier(787878787, 878787878);
		BOOST_CHECK_MESSAGE(false, "no exception thrown");
	}
	catch (std::overflow_error &e)
	{
		BOOST_CHECK_EQUAL(e.what(), "adder() overflow");
	}
}
