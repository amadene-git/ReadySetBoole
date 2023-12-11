#include "readysetboole.h"

int main(int ac, char **av)
{

    if (ac != 2)
        dprintf(2, "error bad arg\n");
    else
        printf("%s\n", (eval_formula(av[1]) == 1 ? "True" : "False"));
}
