#pragma once

#include <lib/Token.h>
#include <optional>
#include <sstream>
template <typename Data>
class AMANode {
public:
  AMANode() : _left(nullptr), _right(nullptr) {
  }

  AMANode(const AMANode&) = default;
  AMANode& operator=(const AMANode&) = default;

  Token<Data> _token;
  std::unique_ptr<AMANode<Data>> _left;
  std::unique_ptr<AMANode<Data>> _right;
};

template <typename T>
std::unique_ptr<AMANode<T>> parseTokens(std::vector<Token<T>>& tokens) {
  std::vector<std::unique_ptr<AMANode<T>>> stackRPN;
  std::unique_ptr<AMANode<T>> currentNode;

  for (auto& token : tokens) {
    currentNode = std::make_unique<AMANode<T>>();
    currentNode->_token = token;

    switch (token._type) {
    case TokenType::BOOL:
    case TokenType::ALPHA:
      break;

    case TokenType::NOT:
      if (stackRPN.empty()) {
        throw std::runtime_error(
            "Error while parsing: unexpected '!' character");
      }
      currentNode->_left = std::move(stackRPN.back());
      stackRPN.pop_back();
      break;

    case TokenType::AND:
    case TokenType::OR:
    case TokenType::XOR:
    case TokenType::IMPLY:
    case TokenType::EQUAL:
      if (stackRPN.size() < 2) {
        throw std::runtime_error("Error while parsing: unexpected operator");
      }

      currentNode->_right = std::move(stackRPN.back());
      stackRPN.pop_back();
      currentNode->_left = std::move(stackRPN.back());
      stackRPN.pop_back();
      break;

    default:
      if (stackRPN.size() != 1) {
        throw std::runtime_error("Error while parsing: unexpected character");
      }
      break;
    }
    stackRPN.push_back(std::move(currentNode));
  }

  if (stackRPN.size() != 1) {
    throw std::runtime_error("Error while parsing: unexpected character");
  }

  return std::move(stackRPN.back());
}

template <typename T>
void print_btree(AMANode<T>& root, std::string filename = "tree.png") {
  std::stringstream dotf;

  dotf << "digraph astgraph {\n\
    node [shape=box, fontsize=12, fontname=\"Courier\", height=.1, style=filled];\n\
    ranksep=.5;\n\
    edge [dir=both, arrowsize=.5, arrowhead=none]\n\n";

  int ncount = 0;
  gendot(&ncount, dotf, root, 0);
  dotf << "\n\n}";

  std::stringstream tmp;
  tmp << "echo '" << dotf.str() << "' > tmp.dot";

  system(tmp.str().c_str());
  system(std::string("rm -rf " + filename).c_str());
  system(std::string("dot -Tpng -o " + filename + " tmp.dot").c_str());
  system("rm -rf tmp.dot");
  system(std::string("xdg-open " + filename + " 2> /dev/null").c_str());
}

template <typename T>
void gendot(int* ncount, std::stringstream& dotf, AMANode<T>& root, int id) {
  dotf << "node" << id << " [label=\"" << root._token << "\"]\n";

  if (root._left != nullptr) {
    *ncount += 1;
    dotf << "node" << id << " -> node" << *ncount << "\n";
    gendot(ncount, dotf, *root._left, *ncount);
  }
  if (root._right != nullptr) {
    *ncount += 1;
    dotf << "node" << id << " -> node" << *ncount << "\n";
    gendot(ncount, dotf, *root._right, *ncount);
  }
}

template <typename T>
void getPostfixData(AMANode<T>& root, std::ostringstream& oss) {
  if (root._left != nullptr) {
    getPostfixData(*root._left, oss);
  }
  if (root._right != nullptr) {
    getPostfixData(*root._right, oss);
  }
  oss << root._token._data;
}

template <typename T>
std::unique_ptr<AMANode<T>> dup_tree(AMANode<T>& root) {
  auto node = std::make_unique<AMANode<T>>();
  node->_token = root._token;
  if (root._left != nullptr)
    node->_left = dup_tree(*(root._left));
  if (root._right != nullptr)
    node->_right = dup_tree(*(root._right));
  return std::move(node);
}

template <class T>
std::unique_ptr<AMANode<T>>
makeToken(TokenType type,
          std::unique_ptr<AMANode<T>> left,
          std::unique_ptr<AMANode<T>> right = nullptr) {

  auto node = std::make_unique<AMANode<T>>();
  switch (type) {
  case TokenType::NOT:
    node->_token = Token<T>{._type = TokenType::NOT, ._data{'!'}};
    node->_left = std::move(left);
    break;

  case TokenType::OR:
    node->_token = Token<T>{._type = TokenType::OR, ._data{'|'}};
    node->_left = std::move(left);
    node->_right = std::move(right);
    break;

  case TokenType::AND:
    node->_token = Token<T>{._type = TokenType::AND, ._data{'&'}};
    node->_left = std::move(left);
    node->_right = std::move(right);
    break;

  default:
    break;
  }
  return std::move(node);
}

template <class T>
std::unique_ptr<AMANode<T>> NNF_simplifyNOT(std::unique_ptr<AMANode<T>> root) {
  auto node = std::move(root->_left);
  std::unique_ptr<AMANode<T>> left;
  std::unique_ptr<AMANode<T>> right;

  switch (node->_token._type) {
  case TokenType::NOT: // !!A == A
    return std::move(node->_left->_left);

  case TokenType::AND: // !(A & B) <===> !A | !B
    left = makeToken(TokenType::NOT, std::move(node->_left));
    right = makeToken(TokenType::NOT, std::move(node->_right));
    return makeToken(TokenType::OR, std::move(left), std::move(right));

  case TokenType::OR: // !(A | B) <===> !A & !B
    left = makeToken(TokenType::NOT, std::move(node->_left));
    right = makeToken(TokenType::NOT, std::move(node->_right));
    return makeToken(TokenType::AND, std::move(left), std::move(right));

  default:
    return std::move(root);
  }
}

template <class T>
std::unique_ptr<AMANode<T>> NNF_simplifyXOR(
    std::unique_ptr<AMANode<T>> root) { // A ^ B -> ( !A & B )  |  ( A & !B )

  auto NOT_Left = makeToken(TokenType::NOT, dup_tree(*(root->_left)));
  auto NOT_Right = makeToken(TokenType::NOT, dup_tree(*(root->_right)));

  auto nodeLeft =
      makeToken(TokenType::AND, std::move(NOT_Left), std::move(root->_right));

  auto nodeRight =
      makeToken(TokenType::AND, std::move(root->_left), std::move(NOT_Right));

  return makeToken(TokenType::OR, std::move(nodeLeft), std::move(nodeRight));
}

template <class T>
std::unique_ptr<AMANode<T>>
NNF_simplifyIMPLY(std::unique_ptr<AMANode<T>> root) { // A > B <===> !A | B
  auto node = makeToken(TokenType::NOT, std::move(root->_left));
  return makeToken(TokenType::OR, std::move(node), std::move(root->_right));
}

template <class T>
std::unique_ptr<AMANode<T>> NNF_simplifyEQUAL(
    std::unique_ptr<AMANode<T>> root) { // A = B -> ( A &  B )  |  ( !A & !B )

  auto NOT_Left = makeToken(TokenType::NOT, dup_tree(*(root->_left)));
  auto NOT_Right = makeToken(TokenType::NOT, dup_tree(*(root->_right)));

  auto nodeLeft = makeToken(TokenType::AND, std::move(root->_left),
                            std::move(root->_right));
  auto nodeRight =
      makeToken(TokenType::AND, std::move(NOT_Left), std::move(NOT_Right));

  return makeToken(TokenType::OR, std::move(nodeLeft), std::move(nodeRight));
}

template <class T>
std::unique_ptr<AMANode<T>> makeNegationNormalForm(AMANode<T>& root) {
  std::unique_ptr<AMANode<T>> left;
  std::unique_ptr<AMANode<T>> right;

  if (root._left != nullptr) {
    left = makeNegationNormalForm(*(root._left));
  }
  if (root._right != nullptr) {
    right = makeNegationNormalForm(*(root._right));
  }

  auto node = std::make_unique<AMANode<T>>();
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

  return std::move(node);
}
