#include <03_BooleanEvaluation/evalFormula.h>

#include <optional>

bool eval_formula(const std::string& formula) {
  std::stack<bool> tokens;
  bool tmp;

  for (int i = 0; formula[i]; i++) {
    if (formula[i] == '0')
      tokens.push(false);
    else if (formula[i] == '1')
      tokens.push(true);
    else if (formula[i] == '!' && tokens.size() >= 1)
      tokens.top() = !tokens.top();
    else if (tokens.size() >= 2) {
      tmp = tokens.top();
      tokens.pop();

      if (formula[i] == '&')
        tokens.top() = tokens.top() & tmp;
      else if (formula[i] == '|')
        tokens.top() = tokens.top() | tmp;
      else if (formula[i] == '^')
        tokens.top() = tokens.top() ^ tmp;
      else if (formula[i] == '>')
        tokens.top() = (!tokens.top()) | tmp;
      else if (formula[i] == '=')
        tokens.top() = tokens.top() == tmp;
      else {
        throw std::runtime_error(
            "Error eval_formula(): Invalid formula unexpected character: " +
            formula[i]);
      }
    } else {
      throw std::runtime_error(
          "Error eval_formula(): (2) Invalid formula unexpected character: "
          + formula[i]);
    }
  }

  if (tokens.size() != 1) {
    throw std::runtime_error(
        "Error eval_formula(): Invalid formula, not enough terms");
  }
  return (tokens.top());
}

// class DataBool {
// public:
//   DataBool(const char c) : _c{c} {
//     if (c == '1') {
//       setValue(true);
//     } else if (c == '0') {
//       setValue(false);
//     }
//   }

//   char getChar() const {
//     return _c;
//   };

//   std::optional<bool> getValue() const {
//     return _value;
//   };

//   void setValue(const bool value) {
//     _value = std::optional<bool>(value);
//   };

// private:
//   char _c;
//   std::optional<bool> _value;
// };

// std::ostream& operator<<(std::ostream& os, const DataBool dataBool) {
//   os << "_c = " << dataBool.getChar() << std::endl;
//   os << "_value = ";
//   if (dataBool.getValue().has_value()) {
//     os << dataBool.getValue().value() << std::endl;

//   } else {
//     os << "undefined" << std::endl;
//   }
//   return os;
// }

// bool computeNode(const Node<DataBool>& root) {
//   bool isLeftRightHasValue = (root._left != nullptr &&
//                               root._left->_token._data.getValue().has_value() &&
//                               root._right != nullptr &&
//                               root._right->_token._data.getValue().has_value());
//   switch (root._token._type) {
//   case TokenType::BOOL:
//     if (root._token._data.getValue().has_value()) {
//       return root._token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(BOOL): has no value");
//     }
//     break;

//   case TokenType::NOT:
//     if (root._left != nullptr &&
//         root._left->_token._data.getValue().has_value()) {
//       return !(root._left->_token._data.getValue().value());
//     } else {
//       throw std::runtime_error("computeNode(NOT): has no value");
//     }
//     break;

//   case TokenType::OR:
//     if (isLeftRightHasValue) {
//       return root._left->_token._data.getValue().value() ||
//              root._right->_token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(OR): has no value");
//     }
//     break;

//   case TokenType::AND:
//     if (isLeftRightHasValue) {
//       return root._left->_token._data.getValue().value() &&
//              root._right->_token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(AND): has no value");
//     }
//     break;

//   case TokenType::XOR:
//     if (isLeftRightHasValue) {
//       return root._left->_token._data.getValue().value() ^
//              root._right->_token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(XOR): has no value");
//     }
//     break;
//   case TokenType::EQUAL:
//     if (isLeftRightHasValue) {
//       return root._left->_token._data.getValue().value() ==
//              root._right->_token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(EQUAL): has no value");
//     }
//     break;

//   case TokenType::IMPLY:
//     if (isLeftRightHasValue) {
//       return !(root._left->_token._data.getValue().value()) ||
//              root._right->_token._data.getValue().value();
//     } else {
//       throw std::runtime_error("computeNode(EQUAL): has no value");
//     }
//     break;

//   default:
//     throw std::runtime_error("Error while compute");
//     break;
//   }
// }

// void computeTree(Node<DataBool>& root) {
//   if (root._left) {
//     computeTree(*root._left);
//   }
//   if (root._right) {
//     computeTree(*root._right);
//   }
//   root._token._data.setValue(computeNode(root));
// }

// bool eval_formula(const std::string& formula) {
//   Btree<DataBool> btree(formula);
//   auto root = btree.getRawTree();
//   computeTree(*root);

//   if (root->_token._data.getValue().has_value()) {
//     return root->_token._data.getValue().value();

//   } else {
//     throw std::runtime_error("eval_formula(): has no value");
//   }
// }
