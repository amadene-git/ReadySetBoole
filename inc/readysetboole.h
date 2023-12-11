#ifndef READYSETBOOLE_H
# define READYSETBOOLE_H

# define BOOL 1
# define OP 2
# define NOT 3

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


typedef struct s_node
{
    struct s_node   *left;
    struct s_node   *right;
    unsigned int    value;
    char            data;
    unsigned int    type;
}               t_node;


uint32_t adder(uint32_t a, uint32_t b);
uint32_t multiplier(uint32_t a, uint32_t b);
// gray machin faut l'ajouter la ...
bool    eval_formula(string str);
void    print_truth_table(string formula);





// *** Utils *** //
void    ft_putnbr_base(uint32_t nb, string base, uint32_t baselen = 0);


// *** Btree *** //
t_node  *new_node();
void    gendot(int *ncount, std::stringstream &dotf, t_node *root, int id);
void    print_btree(t_node *root);
void    clean_tree(t_node *root);
void    print_postfix(t_node *root);





#endif