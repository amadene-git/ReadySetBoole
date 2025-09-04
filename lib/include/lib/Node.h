#pragma once
#include <string>

#define BOOL 1
#define VAR 2
#define NOT 3
#define AND 4
#define OR 5
#define XOR 6
#define IMPLY 7
#define EQUAL 8

class Node {
public:
  Node() = default;
  Node(const Node&) = default;
  Node(char data);

  Node& operator=(const Node&) = default;

public:
  Node operator!();
  Node operator&(Node& rhs);
  Node operator|(Node const& rhs);
  Node operator^(Node& rhs);
  Node operator>(Node& rhs); // p=>q <=> (NOT(p)) OR q
  Node operator==(Node& rhs);

public:
  Node* _left{nullptr};
  Node* _right{nullptr};
  int _value{-1};
  int _type{-1};
  std::string _str{};
  char _data{0};
};
