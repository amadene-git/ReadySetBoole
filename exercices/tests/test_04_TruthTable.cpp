#define BOOST_TEST_MODULE EXERCICE_04_TRUTH_TABLE
#include <boost/test/included/unit_test.hpp>

#include <04_TruthTable/printTruthTable.h>

BOOST_AUTO_TEST_CASE(one_letter_test) {
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("A");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| A | = |\n";
    expectedOutput << "| 0 | 0 |\n";
    expectedOutput << "| 1 | 1 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("B");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| B | = |\n";
    expectedOutput << "| 0 | 0 |\n";
    expectedOutput << "| 1 | 1 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("Z");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| Z | = |\n";
    expectedOutput << "| 0 | 0 |\n";
    expectedOutput << "| 1 | 1 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
}

BOOST_AUTO_TEST_CASE(not_test) {
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("A!");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| A | = |\n";
    expectedOutput << "| 0 | 1 |\n";
    expectedOutput << "| 1 | 0 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("A!!");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| A | = |\n";
    expectedOutput << "| 0 | 0 |\n";
    expectedOutput << "| 1 | 1 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
  {
    std::ostringstream resultOutput;
    std::streambuf* coutPtr = std::cout.rdbuf();
    std::cout.rdbuf(resultOutput.rdbuf());
    print_truth_table("A!!!");
    std::cout.rdbuf(coutPtr);

    std::ostringstream expectedOutput;
    expectedOutput << "| A | = |\n";
    expectedOutput << "| 0 | 1 |\n";
    expectedOutput << "| 1 | 0 |\n";

    BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
  }
}

BOOST_AUTO_TEST_CASE(and_test) {
  std::ostringstream resultOutput;
  std::streambuf* coutPtr = std::cout.rdbuf();
  std::cout.rdbuf(resultOutput.rdbuf());
  print_truth_table("AB&");
  std::cout.rdbuf(coutPtr);

  std::ostringstream expectedOutput;
  expectedOutput << "| A | B | = |\n";
  expectedOutput << "| 0 | 0 | 0 |\n";
  expectedOutput << "| 0 | 1 | 0 |\n";
  expectedOutput << "| 1 | 0 | 0 |\n";
  expectedOutput << "| 1 | 1 | 1 |\n";

  BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
}

BOOST_AUTO_TEST_CASE(basic_test) {
  std::ostringstream resultOutput;
  std::streambuf* coutPtr = std::cout.rdbuf();
  std::cout.rdbuf(resultOutput.rdbuf());
  print_truth_table("AB&C|");
  std::cout.rdbuf(coutPtr);

  std::ostringstream expectedOutput;
  expectedOutput << "| A | B | C | = |\n";
  expectedOutput << "| 0 | 0 | 0 | 0 |\n";
  expectedOutput << "| 0 | 0 | 1 | 1 |\n";
  expectedOutput << "| 0 | 1 | 0 | 0 |\n";
  expectedOutput << "| 0 | 1 | 1 | 1 |\n";
  expectedOutput << "| 1 | 0 | 0 | 0 |\n";
  expectedOutput << "| 1 | 0 | 1 | 1 |\n";
  expectedOutput << "| 1 | 1 | 0 | 1 |\n";
  expectedOutput << "| 1 | 1 | 1 | 1 |\n";

  BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
}

BOOST_AUTO_TEST_CASE(hard_test) {
  std::ostringstream resultOutput;
  std::streambuf* coutPtr = std::cout.rdbuf();
  std::cout.rdbuf(resultOutput.rdbuf());
  print_truth_table("ABC&D|!E||");
  std::cout.rdbuf(coutPtr);

  std::ostringstream expectedOutput;
  expectedOutput << "| A | B | C | D | E | = |\n";
  expectedOutput << "| 0 | 0 | 0 | 0 | 0 | 1 |\n";
  expectedOutput << "| 0 | 0 | 0 | 0 | 1 | 1 |\n";
  expectedOutput << "| 0 | 0 | 0 | 1 | 0 | 0 |\n";
  expectedOutput << "| 0 | 0 | 0 | 1 | 1 | 1 |\n";
  expectedOutput << "| 0 | 0 | 1 | 0 | 0 | 1 |\n";
  expectedOutput << "| 0 | 0 | 1 | 0 | 1 | 1 |\n";
  expectedOutput << "| 0 | 0 | 1 | 1 | 0 | 0 |\n";
  expectedOutput << "| 0 | 0 | 1 | 1 | 1 | 1 |\n";
  expectedOutput << "| 0 | 1 | 0 | 0 | 0 | 1 |\n";
  expectedOutput << "| 0 | 1 | 0 | 0 | 1 | 1 |\n";
  expectedOutput << "| 0 | 1 | 0 | 1 | 0 | 0 |\n";
  expectedOutput << "| 0 | 1 | 0 | 1 | 1 | 1 |\n";
  expectedOutput << "| 0 | 1 | 1 | 0 | 0 | 0 |\n";
  expectedOutput << "| 0 | 1 | 1 | 0 | 1 | 1 |\n";
  expectedOutput << "| 0 | 1 | 1 | 1 | 0 | 0 |\n";
  expectedOutput << "| 0 | 1 | 1 | 1 | 1 | 1 |\n";
  expectedOutput << "| 1 | 0 | 0 | 0 | 0 | 1 |\n";
  expectedOutput << "| 1 | 0 | 0 | 0 | 1 | 1 |\n";
  expectedOutput << "| 1 | 0 | 0 | 1 | 0 | 1 |\n";
  expectedOutput << "| 1 | 0 | 0 | 1 | 1 | 1 |\n";
  expectedOutput << "| 1 | 0 | 1 | 0 | 0 | 1 |\n";
  expectedOutput << "| 1 | 0 | 1 | 0 | 1 | 1 |\n";
  expectedOutput << "| 1 | 0 | 1 | 1 | 0 | 1 |\n";
  expectedOutput << "| 1 | 0 | 1 | 1 | 1 | 1 |\n";
  expectedOutput << "| 1 | 1 | 0 | 0 | 0 | 1 |\n";
  expectedOutput << "| 1 | 1 | 0 | 0 | 1 | 1 |\n";
  expectedOutput << "| 1 | 1 | 0 | 1 | 0 | 1 |\n";
  expectedOutput << "| 1 | 1 | 0 | 1 | 1 | 1 |\n";
  expectedOutput << "| 1 | 1 | 1 | 0 | 0 | 1 |\n";
  expectedOutput << "| 1 | 1 | 1 | 0 | 1 | 1 |\n";
  expectedOutput << "| 1 | 1 | 1 | 1 | 0 | 1 |\n";
  expectedOutput << "| 1 | 1 | 1 | 1 | 1 | 1 |\n";

  BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
}
