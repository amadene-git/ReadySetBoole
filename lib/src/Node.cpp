#include <lib/Node.h>
#include <string>

#define BOOL 1
#define VAR 2
#define NOT 3
#define AND 4
#define OR 5
#define XOR 6
#define IMPLY 7
#define EQUAL 8

Node::Node(char data) : _data{data} {
}

Node Node::operator!() {
  Node ret;
  ret._type = NOT;
  ret._data = '!';
  ret._left = this;
  ret._right = NULL;
  ret._str = "!" + _str;
  if (_value != -1)
    ret._value = !(_value);

  return (ret);
}

Node Node::operator&(Node& rhs) {
  Node ret;
  ret._type = AND;
  ret._data = '&';
  ret._left = this;
  ret._right = &rhs;
  ret._str = "(" + _str + " & " + rhs._str + ")";
  if (_value != -1 && rhs._value != -1)
    ret._value = _value & rhs._value;

  return (ret);
}

Node Node::operator|(Node const& rhs) {
  Node ret;
  ret._type = OR;
  ret._data = '|';
  ret._left = this;
  ret._right = (Node*)&rhs;
  ret._str = "(" + _str + " | " + rhs._str + ")";
  if (_value != -1 && rhs._value != -1)
    ret._value = _value | rhs._value;

  return (ret);
}

Node Node::operator^(Node& rhs) {
  Node ret;
  ret._type = XOR;
  ret._data = '^';
  ret._left = this;
  ret._right = &rhs;
  ret._str = "(" + _str + " ^ " + rhs._str + ")";
  if (_value != -1 && rhs._value != -1)
    ret._value = _value ^ rhs._value;

  return (ret);
}

Node Node::operator>(Node& rhs) // p=>q <=> (NOT(p)) OR q
{
  Node ret;
  ret._type = IMPLY;
  ret._data = '>';
  ret._left = this;
  ret._right = &rhs;
  ret._str = "(" + _str + " > " + rhs._str + ")";
  if (_value != -1 && rhs._value != -1)
    ret._value = (!_value) | rhs._value;

  return (ret);
}

Node Node::operator==(Node& rhs) {
  Node ret;
  ret._type = EQUAL;
  ret._data = '=';
  ret._left = this;
  ret._right = &rhs;
  ret._str = "(" + _str + " = " + rhs._str + ")";
  if (_value != -1 && rhs._value != -1)
    ret._value = _value == rhs._value;

  return (ret);
}
