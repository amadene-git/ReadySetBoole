#pragma once

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

class BytesSet {
public:
  BytesSet() = delete;
  BytesSet(const BytesSet&) = default;
  BytesSet& operator=(const BytesSet&) = default;

  BytesSet(const std::vector<int>& set) : _set(set) {
    _isLastBytesFull = (set.size() % 8 == 0);
    _bytes =
        std::vector<uint8_t>((set.size() / 8) + !_isLastBytesFull, uint8_t{0});
  };
  BytesSet(const std::vector<int>& globalSet, const std::vector<int>& subSet)
      : _set(globalSet) {
    _isLastBytesFull = (_set.size() % 8 == 0);

    _bytes =
        std::vector<uint8_t>((_set.size() / 8) + !_isLastBytesFull, uint8_t{0});

    for (int i = 0; i < globalSet.size(); ++i) {
      auto elem = std::find(subSet.begin(), subSet.end(), globalSet[i]);
      if (elem != subSet.end()) {

        setBit(true, i);
      }
    }
  }
  ~BytesSet() = default;

  void setBit(bool value, int index) {
    if (value == true) {
      _bytes[index / 8] |= (1 << (index % 8));

    } else {
      _bytes[index / 8] &= !(1 << (index % 8));
    }
  }

  bool incrementLastBits() {
    if (_bytes.back() >= (1 << (_set.size() % 8)) - 1) {
      return false;
    }
    ++_bytes.back();
    return true;
  }

  bool incrementBits() {
    for (int i = 0; i < _bytes.size() - !_isLastBytesFull; ++i) {
      if (_bytes[i] < std::numeric_limits<uint8_t>::max()) {
        ++_bytes[i];
        return true;
      } else {
        _bytes[i] = 0;
      }
    }

    if (_isLastBytesFull) {
      return false;
    } else {
      return incrementLastBits();
    }
  }

  std::vector<int> makeSet() {
    uint8_t mask = 1;
    std::vector<int> resultSet;
    size_t setSize = _set.size();

    for (size_t i = 0; i < setSize; ++i) {
      if (_bytes[0] & mask) {
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

  void printBytes() {
    for (auto& byte : _bytes) {
      std::cout << std::bitset<8>(byte) << " ";
    }
    std::cout << std::endl;
  };

  size_t getNbBytes() {
    return _bytes.size();
  }

  void NOT() {
    for (auto& elem : _bytes) {
      elem = 0;
    }
  }

  void AND(BytesSet& rhs) {
    for (int i = 0; i < _bytes.size(); ++i) {
      std::cout << i << std::endl;
    //   printBytes();
    //   rhs.printBytes();
      _bytes[i] &= rhs._bytes[i];
    }
  }
  void OR(const BytesSet& rhs) {
    for (int i = 0; i < _bytes.size(); ++i) {
      _bytes[i] |= rhs._bytes[i];
    }
  }
  void XOR(const BytesSet& rhs) {
    for (int i = 0; i < _bytes.size(); ++i) {
      _bytes[i] ^= rhs._bytes[i];
    }
  }
  void IMPLY(const BytesSet& rhs) {
    for (int i = 0; i < _bytes.size(); ++i) {
      _bytes[i] = (!_bytes[i]) | rhs._bytes[i];
    }
  }
  void EQUAL(const BytesSet& rhs) {
    for (int i = 0; i < _bytes.size(); ++i) {
      if (_bytes[i] != rhs._bytes[i]) {
        NOT();
        return;
      }
    }
  }

public:
  const std::vector<int>& _set;
  std::vector<uint8_t> _bytes;
  bool _isLastBytesFull{0};
};

std::vector<std::vector<int>> powerset(std::vector<int> set);