#define BOOST_TEST_MODULE EXERCICE_00_ADDER

#include "utils.h"
#include <00_Adder/adder.h>
#include <boost/test/included/unit_test.hpp>
#include <chrono>

#include <map>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK(adder(0, 0) == 0);
  BOOST_CHECK(adder(1, 0) == 1);
  BOOST_CHECK(adder(0, 1) == 1);
  BOOST_CHECK(adder(1, 1) == 2);
  BOOST_CHECK(adder(2, 2) == 4);
  BOOST_CHECK(adder(5, 7) == 12);
  BOOST_CHECK(adder(15, 27) == 42);
  BOOST_CHECK(adder(100, 250) == 350);
  BOOST_CHECK(adder(1001, 1002) == 2003);
  BOOST_CHECK(adder(1002, 1001) == 2003);
  BOOST_CHECK(adder(12345, 0) == 12345);
  BOOST_CHECK(adder(0, 67890) == 67890);
  BOOST_CHECK(adder(7, 9) == adder(9, 7));
}

BOOST_AUTO_TEST_CASE(limite_test) {
  auto uintMax = std::numeric_limits<uint32_t>::max();
  BOOST_CHECK(adder(uintMax, 0) == uintMax);
  BOOST_CHECK(adder(0, uintMax) == uintMax);
  BOOST_CHECK(adder(1, uintMax - 1) == uintMax);
}

BOOST_AUTO_TEST_CASE(loop_test) {
  srand(time(NULL));
  for (int i = 0; i < 200 && i >= 0; i++) {
    uint32_t a = (uint32_t)rand() % 2147483648;
    uint32_t b = (uint32_t)rand() % 2147483648;

    BOOST_CHECK_EQUAL(adder(a, b), a + b);
  }
}

BOOST_AUTO_TEST_CASE(overflow_test) {
  try {
    adder(std::numeric_limits<uint32_t>::max(), 1);
    BOOST_CHECK_MESSAGE(false, "no exception thrown");
  } catch (std::overflow_error& e) {
    BOOST_CHECK_EQUAL(e.what(), "adder() overflow");
  }
}

auto test(unsigned int a, unsigned int b) {
  using namespace std::chrono;

  auto start = high_resolution_clock::now();
  for (int i = 0; i < 10000; ++i) {
    adder(a, b);
  }
  auto end = high_resolution_clock::now();
  return duration_cast<nanoseconds>(end - start).count();
}

BOOST_AUTO_TEST_CASE(time_complexity_test) {
  using namespace std::chrono;

  std::map<std::pair<uint32_t, uint32_t>, uint64_t> stats;

  for (int i = 0; i < 5000; ++i) {

    uint32_t a = randomUnsignedInt() % (1 << (i % 32));
    uint32_t b = randomUnsignedInt() % (1 << (i % 32));
    uint32_t duree;
    try {
      duree = test(a, b);
      stats.insert({{a, b}, duree});
    } catch (const std::exception& e) {
      continue;
    }
  }

  std::cout << "Moyenne: " << computeMean(stats) << std::endl;
  std::cout << "Median: " << computeMedian(stats) << std::endl;
  std::cout << "Ecart Type: " << computeStandartDeviation(stats) << std::endl;

  auto begin = stats.begin();
  std::cout << "Plus petit nombre  : a = " << begin->first.first
            << "; b = " << begin->first.second << "; " << begin->second
            << " ms\n";

  auto end = prev(stats.end());
  std::cout << "Plus grand nombre  : a = " << end->first.first
            << "; b = " << end->first.second << "; " << end->second << " ms\n";
}
