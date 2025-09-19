#define BOOST_TEST_MODULE EXERCICE_03_BOOLEAN_EVALUATION
#include <boost/test/included/unit_test.hpp>

#include <03_BooleanEvaluation/evalFormula.h>
#include <chrono>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(eval_formula("1"), true);
  BOOST_CHECK_EQUAL(eval_formula("0"), false);

  BOOST_CHECK_EQUAL(eval_formula("0!"), true);
  BOOST_CHECK_EQUAL(eval_formula("1!"), false);
  BOOST_CHECK_EQUAL(eval_formula("0!!"), false);
  BOOST_CHECK_EQUAL(eval_formula("1!!"), true);
  BOOST_CHECK_EQUAL(eval_formula("0!!!"), true);
  BOOST_CHECK_EQUAL(eval_formula("1!!!"), false);

  BOOST_CHECK_EQUAL(eval_formula("00&"), false);
  BOOST_CHECK_EQUAL(eval_formula("10&"), false);
  BOOST_CHECK_EQUAL(eval_formula("01&"), false);
  BOOST_CHECK_EQUAL(eval_formula("11&"), true);

  BOOST_CHECK_EQUAL(eval_formula("00|"), false);
  BOOST_CHECK_EQUAL(eval_formula("10|"), true);
  BOOST_CHECK_EQUAL(eval_formula("01|"), true);
  BOOST_CHECK_EQUAL(eval_formula("11|"), true);

  BOOST_CHECK_EQUAL(eval_formula("00^"), false);
  BOOST_CHECK_EQUAL(eval_formula("01^"), true);
  BOOST_CHECK_EQUAL(eval_formula("10^"), true);
  BOOST_CHECK_EQUAL(eval_formula("11^"), false);

  BOOST_CHECK_EQUAL(eval_formula("00>"), true);
  BOOST_CHECK_EQUAL(eval_formula("01>"), true);
  BOOST_CHECK_EQUAL(eval_formula("10>"), false);
  BOOST_CHECK_EQUAL(eval_formula("11>"), true);

  BOOST_CHECK_EQUAL(eval_formula("00="), true);
  BOOST_CHECK_EQUAL(eval_formula("01="), false);
  BOOST_CHECK_EQUAL(eval_formula("10="), false);
  BOOST_CHECK_EQUAL(eval_formula("11="), true);

  BOOST_CHECK_EQUAL(eval_formula("10|1&"), true);   // (1 | 0) & 1 == 1
  BOOST_CHECK_EQUAL(eval_formula("101|&"), true);   // 1 & (0 | true) == 1
  BOOST_CHECK_EQUAL(eval_formula("1011||="), true); // ((1 | true) | 0) == 1
}

BOOST_AUTO_TEST_CASE(basic2_test) {
  // ((0∧1) ⊕ (1∨0))
  //    0   ⊕   1    = 1
  BOOST_CHECK_EQUAL(eval_formula("01&10|^"), true);

  // ¬(((1∨0) ⊕ (0∧1) ⊕ (1⊕1)))
  //   ¬( 1   ⊕   0   ⊕   0 )
  //            ¬(1)            = 0
  BOOST_CHECK_EQUAL(eval_formula("10|01&11^^^!"), false);
}

std::string
makeBigFormula(char boolean, char operatorChar, uint32_t size = 100000) {
  std::string formula;

  for (uint32_t i = 0; i < size + 1; ++i) {
    formula += boolean;
  }
  for (uint32_t i = 0; i < size; ++i) {
    formula += operatorChar;
  }

  return formula;
}

BOOST_AUTO_TEST_CASE(big_test) {
  {
    std::string formula("1");

    for (int i = 0; i < 10000; ++i) {
      formula += "0|";
    }

    BOOST_CHECK_EQUAL(eval_formula(formula), true);
  }
  {
    std::string formula("1");

    for (int i = 0; i < 10000; ++i) {
      formula += "1&";
    }

    BOOST_CHECK_EQUAL(eval_formula(formula), true);
  }
  {
    std::string formula("1");

    for (int i = 0; i < 10000; ++i) {
      formula += "!";
    }

    BOOST_CHECK_EQUAL(eval_formula(formula), true);
  }

  {
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('1', '&')), true);
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('0', '&')), false);
  }
  {
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('0', '|')), false);
    auto formula = makeBigFormula('0', '|');
    formula += "1|";
    BOOST_CHECK_EQUAL(eval_formula(formula), true);
  }
  {
    auto formula = makeBigFormula('0', '^');
    formula += "1^";
    BOOST_CHECK_EQUAL(eval_formula(formula), true);
  }
  {
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('1', '=')), true);
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('0', '=')), false);
  }
  {
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('0', '>')), true);
    BOOST_CHECK_EQUAL(eval_formula(makeBigFormula('1', '>')), true);
  }
}

auto testDuration(const std::string& formula) {
  using namespace std::chrono;

  auto start = high_resolution_clock::now();
  eval_formula(formula);
  auto end = high_resolution_clock::now();
  return duration_cast<nanoseconds>(end - start).count();
}

BOOST_AUTO_TEST_CASE(complexity_test) {
  auto formula = makeBigFormula('1', '&', 10);
  std::cout << "test for 10:     " << testDuration(formula) << std::endl;

  formula = makeBigFormula('1', '&', 100);
  std::cout << "test for 100:    " << testDuration(formula) << std::endl;

  formula = makeBigFormula('1', '&', 1000);
  std::cout << "test for 1000:   " << testDuration(formula) << std::endl;

  formula = makeBigFormula('1', '&', 10000);
  std::cout << "test for 10000:  " << testDuration(formula) << std::endl;

  formula = makeBigFormula('1', '&', 100000);
  std::cout << "test for 100000: " << testDuration(formula) << std::endl;
}

BOOST_AUTO_TEST_CASE(error_test) {
  try {
    eval_formula("");
    BOOST_CHECK_MESSAGE(false, "Expected exception");
  } catch (const std::runtime_error& e) {
  }
  try {
    eval_formula("b");
    BOOST_CHECK_MESSAGE(false, "Expected exception");
  } catch (const std::runtime_error& e) {
  }
  try {
    eval_formula("!!");
    BOOST_CHECK_MESSAGE(false, "Expected exception");
  } catch (const std::runtime_error& e) {
  }
}

BOOST_AUTO_TEST_CASE(test) {
  getLitteralForm("ABC&D|!E||");
}
