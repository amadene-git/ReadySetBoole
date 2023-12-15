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


class Node
{
    public:

        Node(char data = 0, string str = "", int type = -1, Node *left = NULL, Node *right = NULL, int value = -1)
        {
            this->data = data;
            this->str = str;
            this->type = type;
            this->left = left;
            this->right = right;
            this->value = value;
        };
        ~Node() {};
        Node& operator=(const Node& rhs)
        {
            if (&rhs != this)
            {
                this->left = rhs.left;
                this->right = rhs.right;
                this->value = rhs.value;
                this->type = rhs.type;
                this->str = rhs.str;
                this->data = rhs.data;
            }
            return (*this);
        };

        Node            *left;
        Node            *right;
        int             value;
        int             type;
        std::string     str;
        char            data;

};


uint32_t adder(uint32_t a, uint32_t b);
uint32_t multiplier(uint32_t a, uint32_t b);
// gray machin faut l'ajouter la ...
bool    eval_formula(char *str);
void    print_truth_table(string formula);
string  negation_normal_form(char *str);





// *** Utils *** //
void    ft_putnbr_base(uint32_t nb, string base, uint32_t baselen = 0);


// *** Btree *** //
Node  *new_node(string data = string(""), int type = -1, Node *left = NULL, Node *right = NULL, int value = -1);

// Node  *new_node();
void    gendot(int *ncount, std::stringstream &dotf, Node *root, int id);
void    print_btree(Node *root);
void    clean_tree(Node *root);
Node  *make_tree(char *str);
void    print_postfix(Node *root);





#endif