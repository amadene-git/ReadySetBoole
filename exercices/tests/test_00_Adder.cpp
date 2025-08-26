#define BOOST_TEST_MODULE EXERCICE_00_ADDER
#include <boost/test/included/unit_test.hpp>
#include <00_Adder/adder.h>

BOOST_AUTO_TEST_CASE(basic_test)
{
	BOOST_CHECK(adder(0, 0) == 0);
	BOOST_CHECK(adder(1, 1) == 2);
	BOOST_CHECK(adder(2, 2) == 4);
	BOOST_CHECK(adder(1, 2) == 3);
	BOOST_CHECK(adder(2, 1) == 3);
	BOOST_CHECK(adder(1001, 1002) == 2003);
	BOOST_CHECK(adder(1002, 1001) == 2003);

	BOOST_CHECK(adder(std::numeric_limits<uint32_t>::max(), 0) == std::numeric_limits<uint32_t>::max());
	BOOST_CHECK(adder(0, std::numeric_limits<uint32_t>::max()) == std::numeric_limits<uint32_t>::max());
}

BOOST_AUTO_TEST_CASE(loop_test)
{
	srand(time(NULL));
	for (int i = 0; i < 200 && i >= 0; i++)
	{
		uint32_t a = (uint32_t)rand() % 2147483648;
		uint32_t b = (uint32_t)rand() % 2147483648;

		BOOST_CHECK_EQUAL(adder(a, b), a + b);
		// std::cout << a << " + " << b << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(overflow_test)
{
	try
	{
		adder(std::numeric_limits<uint32_t>::max(), 1);
		BOOST_CHECK_MESSAGE(false, "no exception thrown");
	}
	catch (std::overflow_error &e)
	{
		BOOST_CHECK_EQUAL(e.what(), "adder() overflow");
	}
}
