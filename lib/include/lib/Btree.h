#pragma once

#include <04_TruthTable/printTruthTable.h>
#include <iostream>
#include <lib/Node.h>
#include <sstream>
#include <string>
#include <vector>

Node* make_tree(char* expr);

template <typename T>
T* dup_tree(T* root) {
  T* node = new T(*root);

  if (root->_left != nullptr)
    node->_left = dup_tree(root->_left);
  if (root->_right != nullptr)
    node->_right = dup_tree(root->_right);

  return (node);
}

template <typename T>
void clean_tree(T* root) {
  if (!root)
    return;
  if (root->_left != nullptr)
    clean_tree(root->_left);
  if (root->_right != nullptr)
    clean_tree(root->_right);

  delete root;
}

template <typename T>
std::string treetostr(T* root) {
  std::string str;

  if (root && root->_left)
    str += treetostr(root->_left);
  if (root && root->_right)
    str += treetostr(root->_right);

  str += std::string(1, root->_data);

  return (str);
}

template <typename T>
void print_postfix(T* root) {
  if (!root)
    return;
  if (root->_left != nullptr)
    print_postfix(root->_left);
  if (root->_right != nullptr)
    print_postfix(root->_right);
  std::cout << root->_data;
}

template <typename T>
void print_btree(T* root, std::string filename = "tree.png") {
  std::stringstream dotf;
  std::string str = treetostr(root);

  std::cout << "**** Print BTree postfix ****\n" << str << std::endl;
  std::cout << "\n" + std::string(29, '*') << std::endl;
  std::cout << "**** Print BTree truthtable ****" << std::endl;
  print_truth_table(str);
  std::cout << std::string(32, '*') << std::endl;

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
void gendot(int* ncount, std::stringstream& dotf, T* root, int id) {
  if (root->_type == BOOL) {
    dotf << "node" << id << " [label=\"" << root->_data << "\"]\n";
  } else if (root->_value == -1) {
    dotf << "node" << id << " [label=\"" << root->_data << "     " << root->_str
         << "\"]\n";
  } else
    dotf << "node" << id << " [label=\"" << root->_value << "    " << root->_str
         << "\"]\n";
  if (root->_value == 0)
    dotf << "node" << id << "[color=\"red\"]\n";
  else if (root->_value == 1)
    dotf << "node" << id << "[color=\"green\"]\n";

  if (root->_left != nullptr) {
    *ncount += 1;
    dotf << "node" << id << " -> node" << *ncount << "\n";
    gendot(ncount, dotf, root->_left, *ncount);
  }
  if (root->_right != nullptr) {
    *ncount += 1;
    dotf << "node" << id << " -> node" << *ncount << "\n";
    gendot(ncount, dotf, root->_right, *ncount);
  }
}
