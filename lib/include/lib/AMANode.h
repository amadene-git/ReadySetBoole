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
    case Token<T>::Type::BOOL:
    case Token<T>::Type::ALPHA:
      break;

    case Token<T>::Type::NOT:
      if (stackRPN.empty()) {
        throw std::runtime_error(
            "Error while parsing: unexpected '!' character");
      }
      currentNode->_left = std::move(stackRPN.back());
      stackRPN.pop_back();
      break;

    case Token<T>::Type::AND:
    case Token<T>::Type::OR:
    case Token<T>::Type::XOR:
    case Token<T>::Type::IMPLY:
    case Token<T>::Type::EQUAL:
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
std::unique_ptr<AMANode<T>> dup_tree(AMANode<T>& root) {
  auto node = std::make_unique<AMANode<T>>();
  node->_token = root._token;
  if (root._left != nullptr)
    node->_left = dup_tree(*(root._left));
  if (root._right != nullptr)
    node->_right = dup_tree(*(root._right));
  return std::move(node);
}