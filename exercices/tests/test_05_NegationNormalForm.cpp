
#define BOOST_TEST_MODULE EXERCICE_05_NEGATION_NORMAL_FORM
#include <boost/test/included/unit_test.hpp>

#include <05_NegationNormalForm/negationNormalForm.h>

BOOST_AUTO_TEST_CASE(basic_test) {
  std::string str = negation_normal_form("0");

  if (str.size() == 0) {
    std::cout << "Error: invalid formula" << std::endl;
  }
  // std::cout << "main ret: "<< str << std::endl;
  // std::cout << str_truth_table(av[1]) << std::endl;
  // std::cout << str_truth_table(str) << std::endl;
}
