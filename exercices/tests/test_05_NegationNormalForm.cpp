
#define BOOST_TEST_MODULE EXERCICE_05_NEGATION_NORMAL_FORM
#include <boost/test/included/unit_test.hpp>

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

// TODO test with big string
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
