#include "eval_formula.hpp"

int main(int ac, char **av) {
  if (ac != 2) {
    std::cerr << "Error: 1 argument expected" << std::endl;
    std::cerr << "Usage: ./eval_formula FORMULA" << std::endl;
    return 1;
  } else {
    try {
      bool ret = eval_formula(av[1]);
      std::cout << "eval_formula(\"" << av[1] << "\") ==> " << std::boolalpha << ret << std::endl;
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  }
  return 0;
}
