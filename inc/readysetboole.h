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
# include <chrono>


using namespace std;

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>



uint32_t adder(uint32_t a, uint32_t b);
uint32_t multiplier(uint32_t a, uint32_t b);
// gray machin faut l'ajouter la ...
bool    eval_formula(char *str);
void    print_truth_table(string formula);
string  negation_normal_form(char *formula);
string conjunctive_normal_form(char *formula);


# include "Btree.hpp"



Node    *make_tree(char *expr);
NNF     *make_NNF_tree(Node *node);
ConjunctiveNormalForm     *make_ConjunctiveNormalForm_tree(NNF *nnftree);
string  str_truth_table(string formula);







#endif