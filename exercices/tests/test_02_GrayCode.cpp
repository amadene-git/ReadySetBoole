#define BOOST_TEST_MODULE EXERCICE_02_GRAY_CODE
#include <boost/test/included/unit_test.hpp>

#include <02_GrayCode/grayCode.h>

#include <bitset>

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

  std::ostringstream oss;
  for (int i = 0; i <= 16; ++i) {
    oss << i << ".\n"
              << "normal " << std::bitset<8>(i) << std::endl;
    oss << "gray   " << std::bitset<8>(gray_code(i)) << std::endl;
  }

  std::ostringstream expectedOutput;
  expectedOutput << "0." << std::endl;
  expectedOutput << "normal 00000000" << std::endl;
  expectedOutput << "gray   00000000" << std::endl;
  expectedOutput << "1." << std::endl;
  expectedOutput << "normal 00000001" << std::endl;
  expectedOutput << "gray   00000001" << std::endl;
  expectedOutput << "2." << std::endl;
  expectedOutput << "normal 00000010" << std::endl;
  expectedOutput << "gray   00000011" << std::endl;
  expectedOutput << "3." << std::endl;
  expectedOutput << "normal 00000011" << std::endl;
  expectedOutput << "gray   00000010" << std::endl;
  expectedOutput << "4." << std::endl;
  expectedOutput << "normal 00000100" << std::endl;
  expectedOutput << "gray   00000110" << std::endl;
  expectedOutput << "5." << std::endl;
  expectedOutput << "normal 00000101" << std::endl;
  expectedOutput << "gray   00000111" << std::endl;
  expectedOutput << "6." << std::endl;
  expectedOutput << "normal 00000110" << std::endl;
  expectedOutput << "gray   00000101" << std::endl;
  expectedOutput << "7." << std::endl;
  expectedOutput << "normal 00000111" << std::endl;
  expectedOutput << "gray   00000100" << std::endl;
  expectedOutput << "8." << std::endl;
  expectedOutput << "normal 00001000" << std::endl;
  expectedOutput << "gray   00001100" << std::endl;
  expectedOutput << "9." << std::endl;
  expectedOutput << "normal 00001001" << std::endl;
  expectedOutput << "gray   00001101" << std::endl;
  expectedOutput << "10." << std::endl;
  expectedOutput << "normal 00001010" << std::endl;
  expectedOutput << "gray   00001111" << std::endl;
  expectedOutput << "11." << std::endl;
  expectedOutput << "normal 00001011" << std::endl;
  expectedOutput << "gray   00001110" << std::endl;
  expectedOutput << "12." << std::endl;
  expectedOutput << "normal 00001100" << std::endl;
  expectedOutput << "gray   00001010" << std::endl;
  expectedOutput << "13." << std::endl;
  expectedOutput << "normal 00001101" << std::endl;
  expectedOutput << "gray   00001011" << std::endl;
  expectedOutput << "14." << std::endl;
  expectedOutput << "normal 00001110" << std::endl;
  expectedOutput << "gray   00001001" << std::endl;
  expectedOutput << "15." << std::endl;
  expectedOutput << "normal 00001111" << std::endl;
  expectedOutput << "gray   00001000" << std::endl;
  expectedOutput << "16." << std::endl;
  expectedOutput << "normal 00010000" << std::endl;
  expectedOutput << "gray   00011000" << std::endl;

  BOOST_CHECK_EQUAL(expectedOutput.str(), oss.str());
}
