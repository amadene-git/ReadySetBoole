#include <07_SAT/sat.h>

bool sat(std::string formula) {
  std::map<char, bool> operands;

  createOperands(operands, formula);

  auto indexMax = std::pow(2, operands.size());
  for (uint32_t i = 0; i < indexMax; ++i) {
    updateOperands(operands, i);
    auto parsedFormula = convertOperandsSymbolToBool(operands, formula);
    if (eval_formula(parsedFormula) == true) {
      return true;
    }
  }
  return false;
}