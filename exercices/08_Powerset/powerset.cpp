#include <08_Powerset/powerset.h>

std::vector<std::vector<int>> powerset(std::vector<int> set) {
  BytesSet bytesSet(set);
  std::vector<std::vector<int>> resultSet;
  bool isMax = true;
  while (isMax) {
    resultSet.push_back(bytesSet.makeSet());
    isMax = bytesSet.incrementBits();
  }
  return resultSet;
}
