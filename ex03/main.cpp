#include "readysetboole.h"

int main(int ac, char **av)
{

    if (ac != 2)
        cerr << "Error: 1 argument expected" << endl;
    else
        cout << eval_formula(av[1]) << endl;

    Node *tree = make_tree(av[1]);

    if (!tree)
    {
        cout << "Error: formula invalid" << endl;
    }
    print_btree(tree);
    clean_tree(tree);

    return (0);
}
