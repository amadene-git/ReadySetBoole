#define BOOST_TEST_MODULE EXERCICE_01_MULTIPLIER
#include <boost/test/included/unit_test.hpp>

#include <01_Multiplier/multiplier.h>
#include <limits>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK_EQUAL(multiplier(6, 7), 42);
  BOOST_CHECK_EQUAL(multiplier(0, 0), 0);
  BOOST_CHECK_EQUAL(multiplier(0, 1), 0);
  BOOST_CHECK_EQUAL(multiplier(12, 0), 0);
  BOOST_CHECK_EQUAL(multiplier(2, 2147483647),
                    std::numeric_limits<uint32_t>::max() - 1);
}

BOOST_AUTO_TEST_CASE(loop_test) {
  srand(time(NULL));

  for (int i = 0; i < 200 && i >= 0; i++) {
    uint32_t a = (uint32_t)rand() % 10000;
    uint32_t b = (uint32_t)rand() % 10000;
    BOOST_CHECK_EQUAL(multiplier(a, b), a * b);
  }
}

BOOST_AUTO_TEST_CASE(basic2_test) {
  BOOST_CHECK(multiplier(0, 0) == 0);
  BOOST_CHECK(multiplier(0, 5) == 0);
  BOOST_CHECK(multiplier(5, 0) == 0);
  BOOST_CHECK(multiplier(1, 1) == 1);
  BOOST_CHECK(multiplier(1, 7) == 7);
  BOOST_CHECK(multiplier(7, 1) == 7);

  // Multiplication simple
  BOOST_CHECK(multiplier(2, 3) == 6);
  BOOST_CHECK(multiplier(4, 5) == 20);

  // Multiplication avec nombres plus grands
  BOOST_CHECK(multiplier(100, 100) == 10000);
  BOOST_CHECK(multiplier(123, 456) == 56088);

  // Vérification commutativité (a * b == b * a)
  BOOST_CHECK(multiplier(25, 40) == multiplier(40, 25));

  // Cas limites
  BOOST_CHECK(multiplier(4294967295u, 1) == 4294967295u); // UINT_MAX * 1
  BOOST_CHECK(multiplier(4294967295u, 0) == 0);           // UINT_MAX * 0
}

BOOST_AUTO_TEST_CASE(overflow_test) {
  try {
    multiplier(787878787, 878787878);
    BOOST_CHECK_MESSAGE(false, "no exception thrown");
  } catch (std::overflow_error& e) {
    BOOST_CHECK_EQUAL(e.what(), "adder() overflow");
  }
}
