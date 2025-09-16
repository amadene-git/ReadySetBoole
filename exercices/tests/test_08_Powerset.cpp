
#define BOOST_TEST_MODULE EXERCICE_08_POWERSET
#include <boost/test/included/unit_test.hpp>

#include <08_Powerset/powerset.h>

#include <bitset>
// Fonction utilitaire pour afficher un ensemble
void printPowerset(const std::vector<std::vector<int>>& ps) {
  std::cout << "{\n";
  for (const auto& subset : ps) {
    std::cout << "  { ";
    for (int num : subset) {
      std::cout << num << " ";
    }
    std::cout << "}\n";
  }
  std::cout << "}\n";
}

BOOST_AUTO_TEST_CASE(basic_test) {
  auto set = powerset(std::vector<int>({1, 2, 3}));
  printPowerset(set);
}
