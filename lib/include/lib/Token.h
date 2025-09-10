#pragma once

#include <fmt/format.h>
#include <string>
#include <vector>

template <class Data>
struct Token {
  enum class Type { BOOL, ALPHA, NOT, AND, OR, XOR, IMPLY, EQUAL, UNDEFINED };
  Type _type{Type::UNDEFINED};
  Data _data;

  template <typename T>
  friend std::ostream& operator<<(std::ostream& os, const Token<T>& token);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Token<T>& token) {
  switch (token._type) {
  case Token<T>::Type::BOOL:
    os << fmt::format("token._type = BOOL");
    break;
  case Token<T>::Type::ALPHA:
    os << fmt::format("token._type = VAR");
    break;
  case Token<T>::Type::NOT:
    os << fmt::format("token._type = NOT");
    break;
  case Token<T>::Type::AND:
    os << fmt::format("token._type = AND");
    break;
  case Token<T>::Type::OR:
    os << fmt::format("token._type = OR");
    break;
  case Token<T>::Type::XOR:
    os << fmt::format("token._type = XOR");
    break;
  case Token<T>::Type::IMPLY:
    os << fmt::format("token._type = IMPLY");
    break;
  case Token<T>::Type::EQUAL:
    os << fmt::format("token._type = EQUAL");
    break;
  case Token<T>::Type::UNDEFINED:
    os << fmt::format("token._type = UNDEFINED");
    break;

  default:
    break;
  }
  os << std::endl << fmt::format("token._data = {}", token._data);
  return os;
}

template <typename T>
std::vector<Token<T>> tokenizeFormula(std::string formula) {

  std::vector<Token<T>> tokens;
  for (auto c : formula) {
    switch (c) {
    case '0':
      tokens.push_back(Token<T>{._type{Token<T>::Type::BOOL}, ._data{c}});
      break;
    case '1':
      tokens.push_back(Token<T>{._type{Token<T>::Type::BOOL}, ._data{c}});
      break;
    case '!':
      tokens.push_back(Token<T>{._type{Token<T>::Type::NOT}, ._data{c}});
      break;
    case '|':
      tokens.push_back(Token<T>{._type{Token<T>::Type::OR}, ._data{c}});
      break;
    case '&':
      tokens.push_back(Token<T>{._type{Token<T>::Type::AND}, ._data{c}});
      break;
    case '^':
      tokens.push_back(Token<T>{._type{Token<T>::Type::XOR}, ._data{c}});
      break;
    case '=':
      tokens.push_back(Token<T>{._type{Token<T>::Type::EQUAL}, ._data{c}});
      break;
    case '>':
      tokens.push_back(Token<T>{._type{Token<T>::Type::IMPLY}, ._data{c}});
      break;
    default:
      if (c >= 'A' && c <= 'Z') {
        tokens.push_back(Token<T>{._type{Token<T>::Type::ALPHA}, ._data{c}});
      }
      throw std::runtime_error(fmt::format("Error bad character: '{}'", c));
      break;
    }
  }

  return tokens;
}
