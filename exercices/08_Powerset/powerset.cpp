#include <08_Powerset/powerset.h>

#include <iostream>

// Fonction qui génère l'ensemble des parties
std::vector<std::vector<int>> powerset(std::vector<int> set) {
  std::vector<std::vector<int>> result;
  int n = set.size();
  int total = 1 << n; // 2^n sous-ensembles

  for (int mask = 0; mask < total; ++mask) {
    std::vector<int> subset;
    for (int i = 0; i < n; ++i) {
      // Vérifie si le i-ème bit est à 1
      if (mask & (1 << i)) {
        subset.push_back(set[i]);
      }
    }
    result.push_back(subset);
  }

  return result;
}
