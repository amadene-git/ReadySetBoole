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
  Node(char data = 0, std::string str = "", int type = -1, Node *left = NULL,
       Node *right = NULL, int value = -1) {
    this->data = data;
    this->str = str;
    this->type = type;
    this->left = left;
    this->right = right;
    this->value = value;
  };
  Node(Node &node) {
    // cout << "Copy constructor called" << endl;

    *this = node;
  };
  ~Node() {};
  Node &operator=(Node const &rhs) {
    // cout << "Node equal operation: " << this << " = " << &rhs << endl;

    if (&rhs != this) {
      this->left = rhs.left;
      this->right = rhs.right;
      this->value = rhs.value;
      this->type = rhs.type;
      this->str = rhs.str;
      this->data = rhs.data;
    }
    return (*this);
  };

  Node operator!() {
    Node ret;

    // cout << "Node operation: NOT " << this << endl;
    ret.type = NOT;
    ret.data = '!';
    ret.left = this;
    ret.right = NULL;
    ret.str = "!" + this->str;
    if (this->value != -1) ret.value = !(this->value);

    return (ret);
  };

  Node operator&(Node &rhs) {
    Node ret;

    // cout << "Node operation: AND " << this << " & " << &rhs << endl;
    ret.type = AND;
    ret.data = '&';
    ret.left = this;
    ret.right = &rhs;
    ret.str = "(" + this->str + " & " + rhs.str + ")";
    if (this->value != -1 && rhs.value != -1)
      ret.value = this->value & rhs.value;

    return (ret);
  };
  Node operator|(Node const &rhs) {
    Node ret;

    // cout << "Node operation: OR " << this << " | " << &rhs << endl;
    ret.type = OR;
    ret.data = '|';
    ret.left = this;
    ret.right = (Node *)&rhs;
    ret.str = "(" + this->str + " | " + rhs.str + ")";
    if (this->value != -1 && rhs.value != -1)
      ret.value = this->value | rhs.value;

    return (ret);
  };
  Node operator^(Node &rhs) {
    Node ret;

    // cout << "Node operation: XOR " << this << " ^ " << &rhs << endl;
    ret.type = XOR;
    ret.data = '^';
    ret.left = this;
    ret.right = &rhs;
    ret.str = "(" + this->str + " ^ " + rhs.str + ")";
    if (this->value != -1 && rhs.value != -1)
      ret.value = this->value ^ rhs.value;

    return (ret);
  };
  Node operator>(Node &rhs)  // p=>q <=> (NOT(p)) OR q
  {
    Node ret;

    // cout << "Node operation: IMPLY " << this << " > " << &rhs << endl;
    ret.type = IMPLY;
    ret.data = '>';
    ret.left = this;
    ret.right = &rhs;
    ret.str = "(" + this->str + " > " + rhs.str + ")";
    if (this->value != -1 && rhs.value != -1)
      ret.value = (!this->value) | rhs.value;

    return (ret);
  };
  Node operator==(Node &rhs) {
    Node ret;

    // cout << "Node operation: EQUAL " << this << " == " << &rhs << endl;
    ret.type = EQUAL;
    ret.data = '=';
    ret.left = this;
    ret.right = &rhs;
    ret.str = "(" + this->str + " = " + rhs.str + ")";
    if (this->value != -1 && rhs.value != -1)
      ret.value = this->value == rhs.value;

    return (ret);
  };

  Node *left;
  Node *right;
  int value;
  int type;
  std::string str;
  char data;
};
