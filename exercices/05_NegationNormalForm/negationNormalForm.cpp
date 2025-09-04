#include <05_NegationNormalForm/negationNormalForm.h>

/*
    !!A ->  A

    !(A & B)    -> !A | !B
    !(A | B)    -> !A & !B

    !(A > B)    ->   A & !B
    !(A ^ B)    -> ( A | !B )  &  (!A |  B )
    !(A = B)    -> ( A |  B )  &  (!A | !B)

    A > B       ->  !A |  B
    A ^ B       -> (!A &  B )  |  ( A & !B )
    A = B       -> ( A &  B )  |  (!A & !B )

*/

NegationNormalForm* make_NNF_tree(Node* root) {
  NegationNormalForm* node = NULL;
  NegationNormalForm* left = NULL;
  NegationNormalForm* right = NULL;

  if (root->_left)
    left = make_NNF_tree(root->_left);
  if (root->_right)
    right = make_NNF_tree(root->_right);

  node = new NegationNormalForm(root->_data, root->_str, root->_type, left,
                                right, root->_value);
  if (node->_type == NOT)
    *node = !*node->_left;
  else if (node->_type == XOR)
    *node = *node->_left ^ *node->_right;
  else if (node->_type == IMPLY)
    *node = *node->_left > *node->_right;
  else if (node->_type == EQUAL)
    *node = *node->_left == *node->_right;

  return (node);
}

std::string negation_normal_form(std::string str) {
  Node* tree = make_tree(const_cast<char*>(str.c_str()));
  if (!tree)
    return ("");

  NegationNormalForm* nnftree = make_NNF_tree(tree);
  if (!nnftree)
    return ("");

  print_btree(nnftree);
  std::string ret = treetostr(nnftree);

  clean_tree(tree);
  clean_tree(nnftree);

  return (ret);
}
