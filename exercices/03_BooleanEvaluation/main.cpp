#include <03_BooleanEvaluation/evalFormula.h>

class DataBool {
public:
  DataBool(const char c) : _c{c} {
    if (c == '1') {
      std::cout << "wesh" << std::endl;
      _value = true;
    } else if (c == '0') {
      std::cout << "coucou" << std::endl;
      _value = false;
    }
  }

  char getChar() const {
    return _c;
  };

  bool getValue() const {
    return _c;
  };

  void setValue(bool value) {
    _value = value;
  };

private:
  char _c;
  bool _value{false};
};
std::ostream& operator<<(std::ostream& os, const DataBool dataBool) {
  os << "_c = " << dataBool.getChar() << std::endl;
  os << "_value = " << dataBool.getValue() << std::endl;
  return os;
}

bool computeNode(Node<DataBool>& root) {
  switch (root._token._type) {
  case TokenType::BOOL:
    if (root._token._data.getChar() == '0') {
      root._token._data.setValue(false);
      return false;
    }

  case TokenType::NOT:
    return !root._token._data.getValue();

  case TokenType::OR:
    return root._left->_token._data.getValue() ||
           root._right->_token._data.getValue();

  case TokenType::AND:
    return root._left->_token._data.getValue() &&
           root._right->_token._data.getValue();

  case TokenType::XOR:
    return root._left->_token._data.getValue() ^
           root._right->_token._data.getValue();

  case TokenType::EQUAL:
    return root._left->_token._data.getValue() ==
           root._right->_token._data.getValue();

  case TokenType::IMPLY:
    return (!root._left->_token._data.getValue()) |
           root._right->_token._data.getValue();

  default:
    throw std::runtime_error("Error while compute");
  }
}

void computeTree(Node<DataBool>& root) {
  if (root._left) {
    computeTree(*root._left);
  }
  if (root._right) {
    computeTree(*root._right);
  }
  root._token._data.setValue(computeNode(root));
}

int main() {
  std::string formula{"0"};
  auto tokens = tokenizeFormula<DataBool>(formula);
  auto btree = parseTokens<DataBool>(tokens);
  computeTree(*btree);
  print_btree(*btree);
  return 0;
}