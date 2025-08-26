#include "print_truth_table.hpp"

int main(int ac, char **av)
{

    if (ac != 2)
    {
        std::cerr << "Bad arg" << std::endl;
        return (1);
    }
    print_truth_table(av[1]);
	std::cout << str_truth_table(av[1]) << std::endl;

}