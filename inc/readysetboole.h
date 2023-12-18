#ifndef READYSETBOOLE_H
# define READYSETBOOLE_H

# define BOOL   1
# define VAR    2
# define NOT    3
# define AND    4
# define OR     5
# define XOR    6
# define IMPLY  7
# define EQUAL  8

# include <iostream>
# include <string>
# include <stack>
# include <vector>
# include <stdexcept>
# include <sstream>
# include <algorithm>


using namespace std;

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <time.h>

uint32_t adder(uint32_t a, uint32_t b);
uint32_t multiplier(uint32_t a, uint32_t b);
// gray machin faut l'ajouter la ...
bool    eval_formula(char *str);
void    print_truth_table(string formula);
string  negation_normal_form(char *str);




# include "Btree.hpp"











// *** Utils *** //
void    ft_putnbr_base(uint32_t nb, string base, uint32_t baselen = 0);


Node  *make_tree(char *expr);
string  str_truth_table(string formula);







#endif