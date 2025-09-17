#pragma once

#include <bitset>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

class SetBits {
public:
  SetBits() = delete;
  SetBits(const std::vector<int>& set) : _set(set) {
    _bits = std::vector<uint8_t>((set.size() / 8) + 1, uint8_t{0});
  };
  ~SetBits() = default;

  void incrementBits() {
    int i = 0;
    for (auto& bit : _bits) {
      if (i == _set.size() / 8 && ) {

      }
        if (bit < std::numeric_limits<uint8_t>::max()) {
          ++bit;
          return;
        } else {
          bit = 0;
        }
      ++i;
    }
  }
  std::vector<int> makeSet() {
    uint8_t mask = 1;
    std::vector<int> resultSet;
    size_t setSize = _set.size();
    for (size_t i = 0; i < setSize; ++i) {
      if (_bits[i / 8] & mask == mask) {
        resultSet.push_back(_set[i]);
      }
      if (mask >= 128) {
        mask = 1;
      } else {
        mask <<= 1;
      }
    }
    return resultSet;
  }

  void print() {
    for (auto& bit : _bits) {
      std::cout << std::bitset<8>(bit) << " ";
    }
    std::cout << std::endl;
  };

private:
  const std::vector<int>& _set;
  std::vector<uint8_t> _bits;
};

std::vector<std::vector<int>> powerset(std::vector<int> set);