#define BOOST_TEST_MODULE EXERCICE_02_GRAY_CODE
#include <boost/test/included/unit_test.hpp>

#include <02_GrayCode/grayCode.h>

BOOST_AUTO_TEST_CASE(subject_test) {
  BOOST_CHECK_EQUAL(gray_code(0), 0);
  BOOST_CHECK_EQUAL(gray_code(1), 1);
  BOOST_CHECK_EQUAL(gray_code(2), 3);
  BOOST_CHECK_EQUAL(gray_code(3), 2);
  BOOST_CHECK_EQUAL(gray_code(4), 6);
  BOOST_CHECK_EQUAL(gray_code(5), 7);
  BOOST_CHECK_EQUAL(gray_code(6), 5);
  BOOST_CHECK_EQUAL(gray_code(7), 4);
  BOOST_CHECK_EQUAL(gray_code(8), 12);
}

BOOST_AUTO_TEST_CASE(increment_test) {
  for (int i = 0; i <= 16; ++i) {
    std::cout << i << ".\n"
              << "normal " << std::bitset<8>(i) << std::endl;
    std::cout << "gray   " << std::bitset<8>(gray_code(i)) << std::endl
              << std::endl;
  }
}
