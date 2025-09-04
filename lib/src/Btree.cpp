#include <lib/Btree.h>

Node* exit_error(std::vector<Node*>& stk, std::string mes = "") {
  while (stk.size()) {
    delete stk.back();
    stk.pop_back();
  }
  std::cerr << mes << std::endl;
  return (NULL);
}

Node* make_tree(char* expr) {
  std::vector<Node*> stk;
  std::vector<Node*> garbage;
  Node* curr = NULL;

  for (int i = 0; expr[i] != 0; i++) {
    curr = new Node(expr[i]);
    garbage.push_back(curr);

    if (expr[i] == '0' || expr[i] == '1') {

      curr->_type = BOOL;
      if (expr[i] == '1') {
        curr->_str = "1";
      }
      if (expr[i] == '0') {
        curr->_str = "0";
      }
      curr->_value = expr[i] - '0';

    } else if (expr[i] >= 'A' && expr[i] <= 'Z') {
      curr->_type = VAR;
      curr->_value = -1;
      curr->_str = std::string(1, expr[i]);

    } else if (expr[i] == '!') {
      if (stk.size() < 1)
        return (exit_error(garbage, "Error: not enough operands"));

      *curr = !(*stk.back());
      stk.pop_back();
    } else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' ||
               expr[i] == '>' || expr[i] == '=') {
      if (stk.size() < 2)
        return (exit_error(garbage, "Error: not enough boolean"));

      curr->_right = stk.back();
      stk.pop_back();
      curr->_left = stk.back();
      stk.pop_back();

      if (expr[i] == '&')
        *curr = *curr->_left & *curr->_right;
      else if (expr[i] == '|')
        *curr = *curr->_left | *curr->_right;
      else if (expr[i] == '^')
        *curr = *curr->_left ^ *curr->_right;
      else if (expr[i] == '>')
        *curr = *curr->_left > *curr->_right;
      else if (expr[i] == '=')
        *curr = *curr->_left == *curr->_right;
    } else
      return (exit_error(garbage, "Error: bad character"));
    stk.push_back(curr);
  }
  if (stk.size() != 1)
    return (exit_error(garbage, "Error: too much boolean"));

  return (stk.back());
}