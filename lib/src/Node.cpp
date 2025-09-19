#include <lib/Node.h>



std::ostream& operator<<(std::ostream& os, const DataStrRepresentation& data) {
  os << "_c = " << data._c << std::endl;
  os << "_str = " << data._str << std::endl;
  return os;
}

std::string appendExpression(Node<DataStrRepresentation>& root) {
  switch (root._token._type) {
  case TokenType::BOOL:
  case TokenType::ALPHA:
    return root._token._data._str;
    break;
  case TokenType::NOT:
    return std::string("(!" + root._left->_token._data._str + ")");
    break;
  case TokenType::AND:
    return std::string("(" + root._left->_token._data._str + " & " +
                       root._right->_token._data._str + ")");
    break;
  case TokenType::OR:
    return std::string("(" + root._left->_token._data._str + " | " +
                       root._right->_token._data._str + ")");
    break;
  case TokenType::XOR:
    return std::string("(" + root._left->_token._data._str + " ^ " +
                       root._right->_token._data._str + ")");
    break;
  case TokenType::IMPLY:
    return std::string("(" + root._left->_token._data._str + " > " +
                       root._right->_token._data._str + ")");
    break;
  case TokenType::EQUAL:
    return std::string("(" + root._left->_token._data._str +
                       " == " + root._right->_token._data._str + ")");
    break;
  case TokenType::UNDEFINED:
    return std::string("(undefined)");
    break;

  default:
    return std::string("(undefined)");

    break;
  }
}

void visitNode(Node<DataStrRepresentation>& root) {
  if (root._left) {
    visitNode(*root._left);
  }
  if (root._right) {
    visitNode(*root._right);
  }
  root._token._data._str = appendExpression(root);
}

std::string getLitteralForm(const std::string formula) {
  Btree<DataStrRepresentation> btree(formula);
  auto root = btree.getRawTree();
  visitNode(*root);
  std::cout << root->_token._data._str << std::endl;
  return root->_token._data._str;
}