#include <06_ConjunctiveNormalForm/conjunctiveNormalForm.h>

/*
std::shared_ptr<Node> distributeOR(const std::shared_ptr<Node>& a,
                                   const std::shared_ptr<Node>& b) {
  if (a->type == NodeType::AND) {
    auto left = distributeOR(a->left, b);
    auto right = distributeOR(a->right, b);
    return std::make_shared<Node>(Node{NodeType::AND, 0, left, right});
  }
  if (b->type == NodeType::AND) {
    auto left = distributeOR(a, b->left);
    auto right = distributeOR(a, b->right);
    return std::make_shared<Node>(Node{NodeType::AND, 0, left, right});
  }
  return std::make_shared<Node>(Node{NodeType::OR, 0, a, b});
}

std::shared_ptr<Node> toCNF(const std::shared_ptr<Node>& root) {
  if (!root)
    return nullptr;
  if (root->type == NodeType::VAR || root->type == NodeType::NOT)
    return root;

  auto left = toCNF(root->left);
  auto right = toCNF(root->right);

  if (root->type == NodeType::OR) {
    return distributeOR(left, right);
  }
  return std::make_shared<Node>(Node{NodeType::AND, 0, left, right});
}

string conjunctive_normal_form(char* formula) {
  Node* tree = make_tree(formula);
  NNF* nnftree = make_NNF_tree(tree);
  ConjunctiveNormalForm* ConjunctiveNormalFormtree =
      make_ConjunctiveNormalForm_tree(nnftree);

  print_btree<ConjunctiveNormalForm>(ConjunctiveNormalFormtree);

  string ret = treetostr(ConjunctiveNormalFormtree);
  clean_tree<Node>(tree);
  clean_tree<NNF>(nnftree);
  clean_tree<ConjunctiveNormalForm>(ConjunctiveNormalFormtree);

  return (ret);
}
*/