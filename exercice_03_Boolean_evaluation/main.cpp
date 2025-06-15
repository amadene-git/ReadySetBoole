#include "readysetboole.h"

int main(int ac, char **av) {
  if (ac != 2) {
    cerr << "Error: 1 argument expected" << endl;
    cerr << "Usage: ./eval_formula FORMULA" << endl;
    return (1);
  } else
    cout << "eval_formula(\"" << av[1] << "\") ==> " << std::boolalpha << eval_formula(av[1]) << endl;

  { // print tree + truth table
    Node *tree = make_tree(av[1]);

    if (!tree) {
      cout << "Error: formula invalid" << endl;
    }
    print_btree(tree);
    clean_tree(tree);
  }
  return (0);
}
