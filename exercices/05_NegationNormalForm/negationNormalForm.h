#pragma once

#include <iostream>
#include <string>

#include <lib/Btree.h>

std::string negation_normal_form(std::string str);

class NegationNormalForm : public Node {
public:
  NegationNormalForm(char data,
                     std::string str,
                     int type,
                     NegationNormalForm* left,
                     NegationNormalForm* right,
                     int value)
      : Node() {
    _data = data;
    _str = str;
    _type = type;
    _left = left;
    _right = right;
    _value = value;
  };

  NegationNormalForm() = default;
  NegationNormalForm(const NegationNormalForm&) = default;
  NegationNormalForm& operator=(const NegationNormalForm&) = default;

  NegationNormalForm operator!() {
    NegationNormalForm ret = *this;

    if (_type == NOT) { // !!A = A
      ret = *_left;
      delete _left;
    } else if (_type == AND) { // !(A & B) -> !A | !B;
      NegationNormalForm* A = new NegationNormalForm(!*_left);
      NegationNormalForm* B = new NegationNormalForm(!*_right);
      ret = *A | *B;
    } else if (_type == OR) { // !(A | B) -> !A & !B;
      NegationNormalForm* A = new NegationNormalForm(!*_left);
      NegationNormalForm* B = new NegationNormalForm(!*_right);
      ret = *A & *B;
    } else {
      ret._type = NOT;
      ret._data = '!';
      ret._left = this;
      ret._right = NULL;
      ret._str = "!" + _str;
      if (_value != -1)
        ret._value = !(_value);

      return (ret);
    }

    delete this;
    return (ret);
  };
  NegationNormalForm operator|(NegationNormalForm const& rhs) {
    NegationNormalForm ret;

    // cout << "NegationNormalForm operation: OR " << this << " | " << &rhs <<
    // endl;
    ret._type = OR;
    ret._data = '|';
    ret._left = this;
    ret._right = (NegationNormalForm*)&rhs;
    ret._str = "(" + _str + " | " + rhs._str + ")";
    if (_value != -1 && rhs._value != -1)
      ret._value = _value | rhs._value;

    return (ret);
  };
  NegationNormalForm operator&(NegationNormalForm const& rhs) {
    NegationNormalForm ret;

    // cout << "NegationNormalForm operation: AND " << this << " & " << &rhs <<
    // endl;
    ret._type = AND;
    ret._data = '&';
    ret._left = this;
    ret._right = (NegationNormalForm*)&rhs;
    ret._str = "(" + _str + " & " + rhs._str + ")";
    if (_value != -1 && rhs._value != -1)
      ret._value = _value & rhs._value;

    return (ret);
  };
  NegationNormalForm
  operator^(NegationNormalForm& rhs) // A ^ B -> (!A &  B )  |  ( A & !B )
  {
    NegationNormalForm ret;
    NegationNormalForm* A = new NegationNormalForm(
        *(new NegationNormalForm(!*dup_tree(this))) & rhs);
    NegationNormalForm* B = new NegationNormalForm(
        *this & *(new NegationNormalForm(!*dup_tree(&rhs))));
    ret = *A | *B;

    return (ret);
  };
  NegationNormalForm operator>(NegationNormalForm& rhs) //    A > B  ->  !A |  B
  {
    // cout << "NegationNormalForm operation: IMPY " << this << " > " << &rhs <<
    // endl;
    NegationNormalForm ret;
    NegationNormalForm* A = new NegationNormalForm(!*this);
    ret = *A | rhs;

    return (ret);
  };
  NegationNormalForm
  operator==(NegationNormalForm& rhs) // A = B  -> ( A &  B )  |  (!A & !B )
  {
    NegationNormalForm ret;
    NegationNormalForm* A = new NegationNormalForm(*this & rhs);
    NegationNormalForm* B =
        new NegationNormalForm(*(new NegationNormalForm(!*dup_tree(this))) &
                               *(new NegationNormalForm(!*dup_tree(&rhs))));
    ret = *A | *B;

    return (ret);
  };

  ~NegationNormalForm() {};

  NegationNormalForm* _left{nullptr};
  NegationNormalForm* _right{nullptr};
};
