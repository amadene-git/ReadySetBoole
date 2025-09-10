
#define BOOST_TEST_MODULE EXERCICE_05_NEGATION_NORMAL_FORM
#include <boost/test/included/unit_test.hpp>

#include <05_NegationNormalForm/negationNormalForm.h>

BOOST_AUTO_TEST_CASE(basic_test) {
  std::cout << negation_normal_form("01^") << std::endl;
}
