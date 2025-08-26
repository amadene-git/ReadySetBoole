#define BOOST_TEST_MODULE EXERCICE_03_BOOLEAN_EVALUATION
#include <boost/test/included/unit_test.hpp>

#include <03_BooleanEvaluation/evalFormula.h>

BOOST_AUTO_TEST_CASE(basic_test)
{
	BOOST_CHECK_EQUAL(eval_formula("0!"), true);
	BOOST_CHECK_EQUAL(eval_formula("1!"), false);

	BOOST_CHECK_EQUAL(eval_formula("00&"), false);
	BOOST_CHECK_EQUAL(eval_formula("10&"), false);
	BOOST_CHECK_EQUAL(eval_formula("01&"), false);
	BOOST_CHECK_EQUAL(eval_formula("11&"), true);

	BOOST_CHECK_EQUAL(eval_formula("00|"), false);
	BOOST_CHECK_EQUAL(eval_formula("10|"), true);
	BOOST_CHECK_EQUAL(eval_formula("01|"), true);
	BOOST_CHECK_EQUAL(eval_formula("11|"), true);

	BOOST_CHECK_EQUAL(eval_formula("00^"), false);
	BOOST_CHECK_EQUAL(eval_formula("10^"), true);
	BOOST_CHECK_EQUAL(eval_formula("01^"), true);
	BOOST_CHECK_EQUAL(eval_formula("11^"), false);

	BOOST_CHECK_EQUAL(eval_formula("00>"), true);
	BOOST_CHECK_EQUAL(eval_formula("10>"), false);
	BOOST_CHECK_EQUAL(eval_formula("01>"), true);
	BOOST_CHECK_EQUAL(eval_formula("11>"), true);

	BOOST_CHECK_EQUAL(eval_formula("00="), true);
	BOOST_CHECK_EQUAL(eval_formula("10="), false);
	BOOST_CHECK_EQUAL(eval_formula("01="), false);
	BOOST_CHECK_EQUAL(eval_formula("11="), true);

	BOOST_CHECK_EQUAL(eval_formula("10|1&"), true);	  // (1 | 0) & 1
	BOOST_CHECK_EQUAL(eval_formula("101|&"), true);	  // 1 & (0 | 1)
	BOOST_CHECK_EQUAL(eval_formula("1011||="), true); // ((1 | 1) | 0) == 1
}
