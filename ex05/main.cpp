#include "readysetboole.h"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        cerr << "Error: 1 arg requiered" << endl;
        return (1);
    }

    // cout << av[1] << endl;
    // print_truth_table(av[1]);


    string str = negation_normal_form(av[1]); 
    cout << str << endl;
    // print_truth_table(str);



}
