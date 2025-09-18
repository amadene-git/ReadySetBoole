#pragma once

#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
  BOOL,
  ALPHA,
  NOT,
  AND,
  OR,
  XOR,
  IMPLY,
  EQUAL,
  UNDEFINED
};

template <class Data>
struct Token {
  TokenType _type{TokenType::UNDEFINED};
  Data _data{'X'};

  template <typename T>
  friend std::ostream& operator<<(std::ostream& os, const Token<T>& token);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Token<T>& token) {

  switch (token._type) {
  case TokenType::BOOL:
    os << "token._type = BOOL";
    break;
  case TokenType::ALPHA:
    os << "token._type = ALPHA";
    break;
  case TokenType::NOT:
    os << "token._type = NOT";
    break;
  case TokenType::AND:
    os << "token._type = AND";
    break;
  case TokenType::OR:
    os << "token._type = OR";
    break;
  case TokenType::XOR:
    os << "token._type = XOR";
    break;
  case TokenType::IMPLY:
    os << "token._type = IMPLY";
    break;
  case TokenType::EQUAL:
    os << "token._type = EQUAL";
    break;
  case TokenType::UNDEFINED:
    os << "token._type = UNDEFINED";
    break;

  default:
    break;
  }
  os << std::endl << "token._data = " << token._data;
  return os;
}

template <typename T>
std::vector<Token<T>> tokenizeFormula(std::string formula) {

  std::vector<Token<T>> tokens;
  for (auto c : formula) {
    switch (c) {
    case '0':
    case '1':
      tokens.push_back(Token<T>{._type{TokenType::BOOL}, ._data{c}});
      break;
    case '!':
      tokens.push_back(Token<T>{._type{TokenType::NOT}, ._data{c}});
      break;
    case '|':
      tokens.push_back(Token<T>{._type{TokenType::OR}, ._data{c}});
      break;
    case '&':
      tokens.push_back(Token<T>{._type{TokenType::AND}, ._data{c}});
      break;
    case '^':
      tokens.push_back(Token<T>{._type{TokenType::XOR}, ._data{c}});
      break;
    case '=':
      tokens.push_back(Token<T>{._type{TokenType::EQUAL}, ._data{c}});
      break;
    case '>':
      tokens.push_back(Token<T>{._type{TokenType::IMPLY}, ._data{c}});
      break;
    default:
      if (c >= 'A' && c <= 'Z') {
        tokens.push_back(Token<T>{._type{TokenType::ALPHA}, ._data{c}});
        break;
      }
      throw std::runtime_error(
          std::string{"Error while tokenization: Bad character: '"} + c + "',");
      break;
    }
  }

  return tokens;
}
