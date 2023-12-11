#include "readysetboole.h"

int main(int ac, char **av)
{

    if (ac != 2)
        cerr << "Error: 1 argument expected" << endl;
    else
        cout << eval_formula(av[1]) << endl;
}
