#include <03_BooleanEvaluation/evalFormula.h>

bool eval_formula(std::string str) {
  std::stack<bool> formula;
  bool tmp;

  for (int i = 0; str[i]; i++) {
    if (str[i] == '0')
      formula.push(false);
    else if (str[i] == '1')
      formula.push(true);
    else if (str[i] == '!' && formula.size() >= 1)
      formula.top() = !formula.top();
    else if (formula.size() >= 2) {
      tmp = formula.top();
      formula.pop();

      if (str[i] == '&')
        formula.top() = formula.top() & tmp;
      else if (str[i] == '|')
        formula.top() = formula.top() | tmp;
      else if (str[i] == '^')
        formula.top() = formula.top() ^ tmp;
      else if (str[i] == '>')
        formula.top() = (!formula.top()) | tmp;
      else if (str[i] == '=')
        formula.top() = formula.top() == tmp;
      else {
        throw std::runtime_error("Error eval_formula(): Invalid formula");
      }
    } else {
      throw std::runtime_error("Error eval_formula(): Invalid formula");
    }
  }

  if (formula.size() != 1) {
    throw std::runtime_error("Error eval_formula(): Invalid formula");
  }
  return (formula.top());
}
