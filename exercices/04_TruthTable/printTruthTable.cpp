#include <04_TruthTable/printTruthTable.h>

void createOperands(std::map<char, bool>& operands, std::string formula) {
  for (char a = 'A'; a <= 'Z'; ++a)
    if (formula.find(a) != std::string::npos)
      operands.insert_or_assign(a, false);
  if (operands.empty())
    throw std::runtime_error("Error formula parsing, operands not found");
}

void updateOperands(std::map<char, bool>& operands, uint8_t value) {
  size_t i{0};
  for (auto& it : std::views::reverse(operands)) {
    it.second = bool((value >> i) & 0x1);
    ++i;
  }
}

void printOperandsSymbol(std::map<char, bool>& operands) {
  for (auto it : operands)
    std::cout << fmt::format("| {} ", it.first);
  std::cout << "| = |" << std::endl;
}

void printOperandsAndResultValue(std::map<char, bool>& operands, int result) {
  for (auto it : operands)
    std::cout << fmt::format("| {} ", int{it.second});
  std::cout << fmt::format("| {} |", result) << std::endl;
}

std::string convertOperandsSymbolToBool(std::map<char, bool> operands,
                                        std::string formulaCopy) {
  for (auto [key, value] : operands) {
    char a = value + '0';
    std::replace(formulaCopy.begin(), formulaCopy.end(), key, a);
  }
  return formulaCopy;
}


void print_truth_table(std::string formula) {
  std::map<char, bool> operands;

  createOperands(operands, formula);
  printOperandsSymbol(operands);

  auto indexMax = std::pow(2, operands.size());
  for (uint32_t i = 0; i < indexMax; ++i) {
    updateOperands(operands, i);
    auto parsedFormula = convertOperandsSymbolToBool(operands, formula);
    auto result = eval_formula(parsedFormula);
    printOperandsAndResultValue(operands, result);
  }
}