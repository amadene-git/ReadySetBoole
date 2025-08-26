#define BOOST_TEST_MODULE EXERCICE_04_TRUTH_TABLE
#include <boost/test/included/unit_test.hpp>

#include <04_TruthTable/printTruthTable.h>

BOOST_AUTO_TEST_CASE(basic_test)
{
	std::ostringstream resultOutput;
	std::streambuf *coutPtr = std::cout.rdbuf();
	std::cout.rdbuf(resultOutput.rdbuf());
	print_truth_table("AB&C|");
	std::cout.rdbuf(coutPtr);

	std::ostringstream expectedOutput;
	expectedOutput << "| A | B | C | = |\n";
	expectedOutput << "| 0 | 0 | 0 | 0 |\n";
	expectedOutput << "| 0 | 0 | 1 | 1 |\n";
	expectedOutput << "| 0 | 1 | 0 | 0 |\n";
	expectedOutput << "| 0 | 1 | 1 | 1 |\n";
	expectedOutput << "| 1 | 0 | 0 | 0 |\n";
	expectedOutput << "| 1 | 0 | 1 | 1 |\n";
	expectedOutput << "| 1 | 1 | 0 | 1 |\n";
	expectedOutput << "| 1 | 1 | 1 | 1 |\n";

	BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
}
