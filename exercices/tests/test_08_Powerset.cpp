
#define BOOST_TEST_MODULE EXERCICE_08_POWERSET
#include <boost/test/included/unit_test.hpp>

#include <08_Powerset/powerset.h>

#include <bitset>

bool vectorCmp(std::vector<int>& a, std::vector<int>& b) {
  if (a.size() != b.size()) {
    return false;
  }

  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

void printPowerset(std::vector<std::vector<int>> set) {
  for (auto subset : set) {
    std::cout << "{ ";
    for (auto i : subset) {
      std::cout << i << ", ";
    }
    std::cout << " }, " << std::endl;
  }
}

BOOST_AUTO_TEST_CASE(basic_test) {
  auto set = powerset(std::vector<int>({1, 2, 3}));
  printPowerset(set);
}

BOOST_AUTO_TEST_CASE(bytesSet_getSize_test) {
  {
    std::vector<int> set;
    BytesSet bytesSet(set);
    BOOST_CHECK_EQUAL(bytesSet.getNbBytes(), 0);
  }
  {
    std::vector<int> set(7);
    BytesSet bytesSet(set);
    BOOST_CHECK_EQUAL(bytesSet.getNbBytes(), 1);
  }
  {
    std::vector<int> set(8);
    BytesSet bytesSet(set);
    BOOST_CHECK_EQUAL(bytesSet.getNbBytes(), 1);
  }
  {
    std::vector<int> set(9);
    BytesSet bytesSet(set);
    BOOST_CHECK_EQUAL(bytesSet.getNbBytes(), 2);
  }
}

BOOST_AUTO_TEST_CASE(bytesSet_increment_test) {
  {
    std::vector<int> set(8);
    BytesSet bytesSet(set);

    int i = 0;
    while (bytesSet.incrementBits()) {
      ++i;
    }
    BOOST_CHECK_EQUAL(i, 255);
  }
  {
    std::vector<int> set(9);
    BytesSet bytesSet(set);

    int i = 0;
    while (bytesSet.incrementBits()) {
      ++i;
    }
    BOOST_CHECK_EQUAL(i, 511);
  }
}

BOOST_AUTO_TEST_CASE(bytesSet_makeSet_test) {
  {
    std::vector<int> set({1, 2, 3});
    BytesSet bytesSet(set);

    auto subset = bytesSet.makeSet();
    std::vector<int> expectedSet;
    BOOST_CHECK(vectorCmp(subset, expectedSet));

    bytesSet.incrementBits();
    subset = bytesSet.makeSet();
    expectedSet.push_back(1);
    BOOST_CHECK(vectorCmp(subset, expectedSet));
  }
}

BOOST_AUTO_TEST_CASE(test) {
  {
    auto set = powerset({1, 2, 3, 4, 5, 6, 7, 8, 9});
    printPowerset(set);
    BOOST_CHECK_EQUAL(set.size(), pow(2, 9));
  }
  {
    auto set = powerset({});
    printPowerset(set);
  }
}