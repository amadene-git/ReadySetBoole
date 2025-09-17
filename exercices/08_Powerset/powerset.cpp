#include <08_Powerset/powerset.h>

#include <bitset>
#include <iostream>
#include <cmath>

// Fonction qui génère l'ensemble des parties
std::vector<std::vector<int>> powerset(std::vector<int> set) {
  SetBits setBits(set);
  std::vector<std::vector<int>> resultSet;
  for (int i = 0; i < pow(2, set.size()); ++i) {
    setBits.incrementBits();
    resultSet.push_back(setBits.makeSet());
  }
}
