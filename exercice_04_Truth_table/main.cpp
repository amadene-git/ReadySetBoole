#include "readysetboole.h"

int main(int ac, char **av)
{

    if (ac != 2)
    {
        cerr << "Bad arg" << endl;
        return (1);
    }
    print_truth_table(av[1]);

}