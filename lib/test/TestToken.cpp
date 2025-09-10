#define BOOST_TEST_MODULE EXERCICE_04_TRUTH_TABLE
#include <boost/test/included/unit_test.hpp>

#include <lib/AMANode.h>
#include <lib/Token.h>

template <typename T>
void print_postfix(std::unique_ptr<AMANode<T>> root) {
  if (!root)
    return;
  if (root->_left != nullptr)
    print_postfix(std::move(root->_left));
  if (root->_right != nullptr)
    print_postfix(std::move(root->_right));
  std::cout << root->_token << std::endl;
}

BOOST_AUTO_TEST_CASE(basic_test) {
//   auto tokens = tokenizeFormula<char>("01^");

//   for (auto token : tokens) {
//     std::cout << token << std::endl;
//   }
//   auto node = parseTokens<char>(tokens);
//   std::cout << "print postfix" << std::endl;
//   print_btree<char>(*node);

//   sleep(5);

//   auto nnf = makeNegationNormalForm(*node);
//   print_btree<char>(*nnf);
//   std::ostringstream oss;
//   getPostfixData(*nnf, oss);
//   std::cout << oss.str();
  //   auto copy = dup_tree<char>(*node);
  //   copy->_left->_token._data = 'X';
  //   print_btree<char>(*copy);

  //   sleep(5);
  //   print_btree<char>(*node);
}