#include <05_NegationNormalForm/negationNormalForm.h>

namespace {
template <class T>
std::unique_ptr<Node<T>> NNF_simplifyNOT(std::unique_ptr<Node<T>> root) {
  auto node = std::move(root->_left);
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;

  switch (node->_token._type) {
  case TokenType::NOT: // !!A <===> A
    return std::move(node->_left);

  case TokenType::AND: // !(A & B) <===> !A | !B
    left = makeToken(TokenType::NOT, std::move(node->_left));
    right = makeToken(TokenType::NOT, std::move(node->_right));
    return makeToken(TokenType::OR, std::move(left), std::move(right));

  case TokenType::OR: // !(A | B) <===> !A & !B
    left = makeToken(TokenType::NOT, std::move(node->_left));
    right = makeToken(TokenType::NOT, std::move(node->_right));
    return makeToken(TokenType::AND, std::move(left), std::move(right));

  default:
    root->_left = std::move(node);
    return (root);
  }
}

template <class T>
std::unique_ptr<Node<T>> NNF_simplifyXOR(
    std::unique_ptr<Node<T>> root) { // A ^ B <===> ( !A & B )  |  ( A & !B )

  auto NOT_Left = makeToken(TokenType::NOT, Btree<T>::dupTree(*(root->_left)));
  auto NOT_Right = makeToken(TokenType::NOT, Btree<T>::dupTree(*(root->_right)));

  auto nodeLeft =
      makeToken(TokenType::AND, std::move(NOT_Left), std::move(root->_right));

  auto nodeRight =
      makeToken(TokenType::AND, std::move(root->_left), std::move(NOT_Right));

  return makeToken(TokenType::OR, std::move(nodeLeft), std::move(nodeRight));
}

template <class T>
std::unique_ptr<Node<T>>
NNF_simplifyIMPLY(std::unique_ptr<Node<T>> root) { // A > B <===> !A | B
  auto node = makeToken(TokenType::NOT, std::move(root->_left));
  return makeToken(TokenType::OR, std::move(node), std::move(root->_right));
}

template <class T>
std::unique_ptr<Node<T>> NNF_simplifyEQUAL(
    std::unique_ptr<Node<T>> root) { // A = B <===> ( A &  B )  |  ( !A & !B )

  auto NOT_Left = makeToken(TokenType::NOT, Btree<T>::dupTree(*(root->_left)));
  auto NOT_Right = makeToken(TokenType::NOT, Btree<T>::dupTree(*(root->_right)));

  auto nodeLeft = makeToken(TokenType::AND, std::move(root->_left),
                            std::move(root->_right));
  auto nodeRight =
      makeToken(TokenType::AND, std::move(NOT_Left), std::move(NOT_Right));

  return makeToken(TokenType::OR, std::move(nodeLeft), std::move(nodeRight));
}

} // namespace
template <class T>
std::unique_ptr<Node<T>> makeNegationNormalForm(Node<T>& root) {
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;

  if (root._left != nullptr) {
    left = makeNegationNormalForm(*(root._left));
  }
  if (root._right != nullptr) {
    right = makeNegationNormalForm(*(root._right));
  }

  auto node = std::make_unique<Node<T>>();
  node->_token = root._token;
  node->_left = std::move(left);
  node->_right = std::move(right);
  switch (node->_token._type) {
  case TokenType::NOT:
    node = NNF_simplifyNOT(std::move(node));
    break;
  case TokenType::XOR:
    node = NNF_simplifyXOR(std::move(node));
    break;
  case TokenType::IMPLY:
    node = NNF_simplifyIMPLY(std::move(node));
    break;
  case TokenType::EQUAL:
    node = NNF_simplifyEQUAL(std::move(node));
    break;

  default:
    break;
  }

  return (node);
}

template <class T>
std::unique_ptr<Node<T>> loopNegationNormalForm(Node<T>& root) {
  std::ostringstream oss;
  auto nnf = makeNegationNormalForm<char>(root);
  getPostfixData(*nnf, oss);

  std::string strCopy;
  while (oss.str() != strCopy) {
    strCopy = oss.str();
    oss.str("");
    nnf = makeNegationNormalForm<char>(*nnf);
    getPostfixData<char>(*nnf, oss);
  }
  return nnf;
}

std::string negation_normal_form(const std::string& formula) {

  Btree<char> btree(formula);
  auto node = btree.getRawTree();

  auto nnf = loopNegationNormalForm<char>(*node);
  std::ostringstream oss;
  getPostfixData(*nnf, oss);

  return oss.str();
}
