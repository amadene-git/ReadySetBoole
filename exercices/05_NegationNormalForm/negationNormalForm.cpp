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

std::string negation_normal_form(std::string str) {
  auto tokens = tokenizeFormula<char>(str);
  std::cout << "tokenizeFormula" << std::endl;

  auto node = parseTokens<char>(tokens);
  std::cout << "parseTokens" << std::endl;

  auto nnf = makeNegationNormalForm(*node);
  std::cout << "makeNegationNormalForm" << std::endl;

  std::ostringstream oss;
  getPostfixData(*nnf, oss);
  std::cout << oss.str();
  return oss.str();
}
