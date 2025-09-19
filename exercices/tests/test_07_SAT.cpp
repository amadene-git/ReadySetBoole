
#define BOOST_TEST_MODULE EXERCICE_07_SAT
#include <boost/test/included/unit_test.hpp>

#include <07_SAT/sat.h>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(sat("AB|"), true);
  BOOST_CHECK_EQUAL(sat("AB&"), true);
  BOOST_CHECK_EQUAL(sat("AA!&"), false);
  BOOST_CHECK_EQUAL(sat("AA^"), false);
}

BOOST_AUTO_TEST_CASE(several_test) {

  BOOST_CHECK_EQUAL(sat("A"), true);
  BOOST_CHECK_EQUAL(sat("A!"), true);
  BOOST_CHECK_EQUAL(sat("AA&"), true);
  BOOST_CHECK_EQUAL(sat("AA|"), true);
  BOOST_CHECK_EQUAL(sat("AA!&"), false);
  BOOST_CHECK_EQUAL(sat("AB&"), true);
  BOOST_CHECK_EQUAL(sat("AB&!"), true);
  BOOST_CHECK_EQUAL(sat("AB|!"), true);
  BOOST_CHECK_EQUAL(sat("AAAAAAAAAA&&&&&&&&&"), true);

  //   Formule RPN Attendu ABCDEFGHIJKLMNOPQRSTUVWXY &
  //           true ABCDEFGHIJKLMNOPQRSTUVWXY !&true
  // `ABCDEFGHIJKLMNOPQRSTUVWXY !	` ABCDEFGHIJKLMNOPQRSTUVWXY &&
  //       &&&&&&&&&&&&&&&&&&&&true ABCDEFGHIJKLMNOPQRSTUVWXY
  //       !&&!&&!&&!&&!&&!&&!&&!&&!&&!true
}
