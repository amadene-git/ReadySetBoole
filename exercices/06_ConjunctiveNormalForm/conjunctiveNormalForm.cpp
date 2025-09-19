#include <06_ConjunctiveNormalForm/conjunctiveNormalForm.h>

//(A ∨ (B ∧ C)) ⇔ ((A ∨ B) ∧ (A ∨ C))

template <class T>
std::unique_ptr<Node<T>> distributeOR(std::unique_ptr<Node<T>> a,
                                      std::unique_ptr<Node<T>> b,
                                      std::unique_ptr<Node<T>> c) {
  auto aCopy = Btree<T>::dupTree(*a);

  auto leftNode = makeToken<T>(TokenType::OR, std::move(a), std::move(b));
  auto rightNode = makeToken<T>(TokenType::OR, std::move(aCopy), std::move(c));

  return makeToken<T>(TokenType::AND, std::move(leftNode),
                      std::move(rightNode));
}

template <class T>
std::unique_ptr<Node<T>> makeDistribution(Node<T>& root) {
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;

  if (root._left != nullptr) {
    left = makeDistribution(*(root._left));
  }
  if (root._right != nullptr) {
    right = makeDistribution(*(root._right));
  }

  auto node = std::make_unique<Node<T>>();
  node->_token = root._token;
  node->_left = std::move(left);
  node->_right = std::move(right);
  if (node->_token._type == TokenType::OR) {
    if (node->_left->_token._type == TokenType::AND) {

      return distributeOR(std::move(node->_right),
                          std::move(node->_left->_right),
                          std::move(node->_left->_left));
    }
    if (node->_right->_token._type == TokenType::AND) {
      return distributeOR(std::move(node->_left),
                          std::move(node->_right->_right),
                          std::move(node->_right->_left));
    }
  }
  return (node);
}

template <class T>
std::unique_ptr<Node<T>> moveOperatorsToRight(Node<T>& root) {
  std::unique_ptr<Node<T>> left;
  std::unique_ptr<Node<T>> right;

  if (root._left != nullptr) {
    left = moveOperatorsToRight(*(root._left));
  }
  if (root._right != nullptr) {
    right = moveOperatorsToRight(*(root._right));
  }

  auto node = std::make_unique<Node<T>>();
  node->_token = root._token;

  switch (node->_token._type) {
  case TokenType::OR:
    if (left->_token._type == TokenType::OR) {
      node->_left = std::move(left->_left);
      left->_left = std::move(left->_right);
      left->_right = std::move(right);
      node->_right = std::move(left);
      return moveOperatorsToRight(*node);
    }
    [[fallthrough]];
  case TokenType::AND:
    if (left->_token._type == TokenType::AND) {
      node->_left = std::move(left->_left);
      left->_left = std::move(left->_right);
      left->_right = std::move(right);
      node->_right = std::move(left);
      return moveOperatorsToRight(*node);
    }
    [[fallthrough]];

  default:
    node->_left = std::move(left);
    node->_right = std::move(right);

    break;
  }
  return (node);
}

std::string conjunctive_normal_form(std::string formula) {
  Btree<char> btree(formula);
  auto node = btree.getRawTree();
  auto nnf = loopNegationNormalForm<char>(*node);

  auto cnf = makeDistribution<char>(*nnf);
  auto finalCnf = moveOperatorsToRight(*cnf);

  std::ostringstream oss;
  getPostfixData(*finalCnf, oss);

  return oss.str();
}
