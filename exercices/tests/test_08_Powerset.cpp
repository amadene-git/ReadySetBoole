
#define BOOST_TEST_MODULE EXERCICE_08_POWERSET
#include <boost/test/included/unit_test.hpp>

#include <08_Powerset/powerset.h>

#include <bitset>


BOOST_AUTO_TEST_CASE(basic_test) {
  auto set = powerset(std::vector<int>({1, 2, 3}));
  // printPowerset(set);
}
