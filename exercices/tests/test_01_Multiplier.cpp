#define BOOST_TEST_MODULE EXERCICE_01_MULTIPLIER
#include <boost/test/included/unit_test.hpp>

#include "utils.h"
#include <01_Multiplier/multiplier.h>
#include <chrono>
#include <limits>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(multiplier(6, 7), 42);
  BOOST_CHECK_EQUAL(multiplier(0, 0), 0);
  BOOST_CHECK_EQUAL(multiplier(0, 1), 0);
  BOOST_CHECK_EQUAL(multiplier(12, 0), 0);
  BOOST_CHECK_EQUAL(multiplier(2, 2147483647), UINT_MAX - 1);

  BOOST_CHECK(multiplier(0, 0) == 0);
  BOOST_CHECK(multiplier(0, 5) == 0);
  BOOST_CHECK(multiplier(5, 0) == 0);
  BOOST_CHECK(multiplier(1, 1) == 1);
  BOOST_CHECK(multiplier(1, 7) == 7);
  BOOST_CHECK(multiplier(7, 1) == 7);

  BOOST_CHECK(multiplier(2, 3) == 6);
  BOOST_CHECK(multiplier(4, 5) == 20);

  BOOST_CHECK(multiplier(100, 100) == 10000);
  BOOST_CHECK(multiplier(123, 456) == 56088);

  BOOST_CHECK(multiplier(25, 40) == multiplier(40, 25));

  // Cas limites
  BOOST_CHECK(multiplier(UINT_MAX, 1) == UINT_MAX);
  BOOST_CHECK(multiplier(UINT_MAX, 0) == 0);
}

BOOST_AUTO_TEST_CASE(loop_test) {
  srand(time(NULL));

  for (int i = 0; i < 200 && i >= 0; i++) {
    uint32_t a = (uint32_t)rand() % 10000;
    uint32_t b = (uint32_t)rand() % 10000;
    BOOST_CHECK_EQUAL(multiplier(a, b), a * b);
  }
}

BOOST_AUTO_TEST_CASE(overflow_test) {
  try {
    multiplier(787878787, 878787878);
    BOOST_CHECK_MESSAGE(false, "no exception thrown");
  } catch (std::overflow_error& e) {
    BOOST_CHECK_EQUAL(e.what(), "multiplier() overflow");
  }
}

auto test(unsigned int a, unsigned int b) {
  using namespace std::chrono;

  auto start = high_resolution_clock::now();
  for (int i = 0; i < 10000; ++i) {
    multiplier(a, b);
  }
  auto end = high_resolution_clock::now();
  return duration_cast<nanoseconds>(end - start).count();
}

BOOST_AUTO_TEST_CASE(complexity_test) {
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
