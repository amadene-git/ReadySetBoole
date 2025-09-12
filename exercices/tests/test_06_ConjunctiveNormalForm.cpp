
#define BOOST_TEST_MODULE EXERCICE_06_CONJUNCTIVE_NORMAL_FORM
#include <boost/test/included/unit_test.hpp>

#include <06_ConjunctiveNormalForm/conjunctiveNormalForm.h>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(conjunctive_normal_form("AB&!"), "A!B!|");

  BOOST_CHECK_EQUAL(conjunctive_normal_form("AB|!"), "A!B!&");
  BOOST_CHECK_EQUAL(conjunctive_normal_form("AB|C&"), "AB|C&");
  BOOST_CHECK_EQUAL(conjunctive_normal_form("AB|C|D|"), "ABCD|||");
  auto tokens = tokenizeFormula<char>("ABCD|||");
  auto node = parseTokens<char>(tokens);
  print_btree<char>(*node);
  //   auto nnf = loopNegationNormalForm<char>(*node);
  //   auto cnf = makeConjuctiveNormalForm<char>(*nnf);

  // BOOST_CHECK_EQUAL(conjunctive_normal_form("AB&C&D&"), "ABCD&&&");
  // BOOST_CHECK_EQUAL(conjunctive_normal_form("AB&!C!|"), "A!B!C!||");
  // BOOST_CHECK_EQUAL(conjunctive_normal_form("AB|!C!&"), "A!B!C!&&");
}
