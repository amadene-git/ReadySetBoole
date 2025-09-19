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

/*
auto testDuration(const std::string& formula) {
  using namespace std::chrono;
  std::ostringstream resultOutput;
  std::streambuf* coutPtr = std::cout.rdbuf();
  std::cout.rdbuf(resultOutput.rdbuf());

  auto start = high_resolution_clock::now();
  print_truth_table(formula);
  auto end = high_resolution_clock::now();

  std::cout.rdbuf(coutPtr);
  return duration_cast<nanoseconds>(end - start).count();
}

BOOST_AUTO_TEST_CASE(complexity_test) {
  std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::string andSuite;
  std::string formula;
  for (size_t i = 1; i <= 26; ++i) {
    formula = alphabet.substr(0, i) + andSuite;
    std::cout << "test for '" << formula << "' " << i << ":     "
              << testDuration(formula) << std::endl;
    andSuite += "&";
  }
}

BOOST_AUTO_TEST_CASE(all_letter_test) {
  std::ostringstream resultOutput;
  std::streambuf* coutPtr = std::cout.rdbuf();
  std::cout.rdbuf(resultOutput.rdbuf());
  print_truth_table("ABCDEFGHIJKLMNOPQRSTUVWXYZ&&&&&&&&&&&&&&&&&&&&&&&&&");
  std::cout.rdbuf(coutPtr);
  std::ostringstream expectedOutput;

  BOOST_CHECK_EQUAL(expectedOutput.str(), resultOutput.str());
}

BOOST_AUTO_TEST_CASE(several_letter_test) {
  print_truth_table("ABCDEFGHIJKLMNOPQRSTU&&&&&&&&&&&&&&&&&&&&");
}

              sec  milli micro nano
test for  1:               11  323
test for  2:               16  744
test for  3:               35  485
test for  4:               80  711
test for  5:              182  192
test for  6:              495  172
test for  7:           1  120  974
test for  8:           2  681  524
test for  9:           5  617  634
test for  10:         12  607  608
test for  11:         25  822  564
test for  12:         57  811  636
test for  13:        120  434  067
test for  14:        255  007  588
test for  15:        538  742  687
test for  16:    1   143  829  204
test for  17:    2   386  768  772
test for  18:    5   158  201  317
test for  19:   11   062  870  744
test for  20:   24   980  845  811
test for  21:   53   759  409  095
test for  22:  108   841  997  155
test for  23:  262   595  936  657
test for  24:  500   364  236  851
test for  25:  844   953  900  027

*/
