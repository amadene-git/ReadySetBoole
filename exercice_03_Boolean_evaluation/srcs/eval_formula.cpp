#include "eval_formula.hpp"

bool eval_formula(char *str) {
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
        throw std::runtime_error("Error eval_formula(): Bad character");
      }
    } else {
      throw std::runtime_error("Error eval_formula(): Bad character");
      return (0);
    }
  }

  if (formula.size() != 1) {
    std::runtime_error("Error eval_formula(): Bad invalid formula");
    return (0);
  }
  return (formula.top());
}
