
#define BOOST_TEST_MODULE EXERCICE_05_NEGATION_NORMAL_FORM
#include <boost/test/included/unit_test.hpp>

#include <04_TruthTable/printTruthTable.h>
#include <05_NegationNormalForm/negationNormalForm.h>

/*
    !!A ->  A

    !(A & B)    -> !A | !B
    !(A | B)    -> !A & !B

    !(A > B)    ->   A & !B
    !(A ^ B)    -> ( A | !B )  &  (!A |  B )
    !(A = B)    -> ( A |  B )  &  (!A | !B)

    A > B       ->  !A |  B
    A ^ B       -> (!A &  B )  |  ( A & !B )
    A = B       -> ( A &  B )  |  (!A & !B )

*/

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(negation_normal_form("0!!"), "0");
  BOOST_CHECK_EQUAL(negation_normal_form("A!!"), "A");

  BOOST_CHECK_EQUAL(negation_normal_form("AB&!"), "A!B!|");
  BOOST_CHECK_EQUAL(negation_normal_form("AB|!"), "A!B!&");

  BOOST_CHECK_EQUAL(negation_normal_form("AB>"), "A!B|");
  BOOST_CHECK_EQUAL(negation_normal_form("AB="), "AB&A!B!&|");

  BOOST_CHECK_EQUAL(negation_normal_form("AB>!"), "AB!&");
  BOOST_CHECK_EQUAL(negation_normal_form("AB^!"), "AB!|A!B|&");
  BOOST_CHECK_EQUAL(negation_normal_form("AB=!"), "A!B!|AB|&");

  BOOST_CHECK_EQUAL(negation_normal_form("AB|C&!"), "A!B!&C!|");
}

bool checkNegationNormalForm(std::string formula) {
  std::string nnfFormula = negation_normal_form(formula);
  for (size_t i = 0; i < nnfFormula.size(); ++i) {
    if (nnfFormula[i] != '!' && nnfFormula[i] != '&' && nnfFormula[i] != '|' &&
        (nnfFormula[i] < 'A' || nnfFormula[i] > 'Z')) {
      return false;
    }
    if (nnfFormula[i] == '!' &&
        (nnfFormula[i - 1] < 'A' || nnfFormula[i - 1] > 'Z')) {
      return false;
    }
  }

  std::streambuf* coutPtr = std::cout.rdbuf();

  std::ostringstream nnfTruthTable;
  std::cout.rdbuf(nnfTruthTable.rdbuf());
  print_truth_table(nnfFormula);

  std::ostringstream oldTruthTable;
  std::cout.rdbuf(oldTruthTable.rdbuf());
  print_truth_table(formula);

  std::cout.rdbuf(coutPtr);

  if (oldTruthTable.str() != nnfTruthTable.str()) {
    return false;
  }
  return true;
}

BOOST_AUTO_TEST_CASE(checkValid_test) {
  BOOST_CHECK(checkNegationNormalForm("ABC&D|!E||"));
  BOOST_CHECK(checkNegationNormalForm("AB|CD&EF^^^!"));
  
}
