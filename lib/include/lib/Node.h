#pragma once

#include <chrono>
#include <fstream>
#include <lib/Token.h>
#include <memory>
#include <optional>
#include <sstream>

template <typename Data>
class Node {
public:
  Node() : _left(nullptr), _right(nullptr) {
  }

  Node(const Node&) = default;
  Node& operator=(const Node&) = default;

  Token<Data> _token;
  std::unique_ptr<Node<Data>> _left;
  std::unique_ptr<Node<Data>> _right;
};

template <typename Data>
class Btree {
public:
  Btree() = delete;
  Btree(const std::string formula) {
    auto tokens = tokenizeFormula<Data>(formula);
    _rawTree = std::move(parseTokens(tokens));
  }
  ~Btree() = default;

  std::unique_ptr<Node<Data>> getRawTreeCopy();
  std::unique_ptr<Node<Data>> getRawTree();

  static std::unique_ptr<Node<Data>> dupTree(Node<Data>& root);

  std::unique_ptr<Node<Data>> parseTokens(std::vector<Token<Data>>& tokens);

private:
  std::unique_ptr<Node<Data>> _rawTree;
};

template <class Data>
std::unique_ptr<Node<Data>> Btree<Data>::getRawTreeCopy() {
  if (_rawTree == nullptr) {
    throw std::runtime_error("Btree::getRawTreeCopy(): _rawTree is null");
  }
  return dupTree(*_rawTree);
}

template <class Data>
std::unique_ptr<Node<Data>> Btree<Data>::getRawTree() {
  if (_rawTree == nullptr) {
    throw std::runtime_error("Btree::getRawTree(): _rawTree is null");
  }
  return std::move(_rawTree);
};

template <class Data>
std::unique_ptr<Node<Data>> Btree<Data>::dupTree(Node<Data>& root) {
  auto node = std::make_unique<Node<Data>>();
  node->_token = root._token;
  if (root._left != nullptr)
    node->_left = dupTree(*(root._left));
  if (root._right != nullptr)
    node->_right = dupTree(*(root._right));
  return node;
}

template <typename T>
std::unique_ptr<Node<T>> Btree<T>::parseTokens(std::vector<Token<T>>& tokens) {
  std::vector<std::unique_ptr<Node<T>>> stackRPN;
  std::unique_ptr<Node<T>> currentNode;

  for (auto& token : tokens) {
    currentNode = std::make_unique<Node<T>>();
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
void print_btree(Node<T>& root, std::string filename = "tree.png") {
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
void gendot(int* ncount, std::stringstream& dotf, Node<T>& root, int id) {
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
void getPostfixData(Node<T>& root, std::ostringstream& oss) {
  if (root._left != nullptr) {
    getPostfixData(*root._left, oss);
  }
  if (root._right != nullptr) {
    getPostfixData(*root._right, oss);
  }
  oss << root._token._data;
}

template <class T>
std::unique_ptr<Node<T>> makeToken(TokenType type,
                                   std::unique_ptr<Node<T>> left,
                                   std::unique_ptr<Node<T>> right = nullptr) {

  auto node = std::make_unique<Node<T>>();
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
  return node;
}

class DataStrRepresentation {
public:
  DataStrRepresentation(const char c) {
    _c = c;
    _str = c;
  }

  char _c;
  std::string _str;
};

std::ostream& operator<<(std::ostream& os, const DataStrRepresentation& data);

std::string appendExpression(Node<DataStrRepresentation>& root);

void visitNode(Node<DataStrRepresentation>& root);

std::string getLitteralForm(const std::string formula);