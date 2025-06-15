#include "readysetboole.h"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        cerr << "Error: 1 arg requiered" << endl;
        return (1);
    }

    string str = negation_normal_form(av[1]);

    if (str.size() == 0)
    {
        cout << "Error: invalid formula" << endl;
        return (0); 
    }
    cout << "main ret: "<< str << endl;
    cout << str_truth_table(av[1]) << endl;
    cout << str_truth_table(str) << endl;



}
