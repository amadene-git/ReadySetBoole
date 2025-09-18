#pragma once
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <random>
using namespace std;

unsigned int randomUnsignedInt() {
  static random_device rd;
  static mt19937 gen(rd());

  static uniform_int_distribution<unsigned int> dist(0, UINT_MAX);

  return dist(gen);
}

double
computeMean(const std::map<std::pair<uint32_t, uint32_t>, uint64_t>& data) {
  if (data.empty())
    return 0.0;

  double somme = 0.0;
  for (const auto& pair : data) {
    somme += pair.second;
  }
  return somme / data.size();
}

double
computeMedian(const std::map<std::pair<uint32_t, uint32_t>, uint64_t>& data) {
  if (data.empty())
    return 0.0;

  vector<double> valeurs;
  for (const auto& pair : data) {
    valeurs.push_back(pair.second);
  }

  sort(valeurs.begin(), valeurs.end());

  size_t n = valeurs.size();
  if (n % 2 == 0) {
    return (valeurs[n / 2 - 1] + valeurs[n / 2]) / 2.0;
  } else {
    return valeurs[n / 2];
  }
}

double computeStandartDeviation(
    const std::map<std::pair<uint32_t, uint32_t>, uint64_t>& data) {
  if (data.size() < 2)
    return 0.0;

  double moyenne = computeMean(data);
  double sommeCarres = 0.0;

  for (const auto& pair : data) {
    double diff = pair.second - moyenne;
    sommeCarres += diff * diff;
  }

  return sqrt(sommeCarres / data.size());
}
