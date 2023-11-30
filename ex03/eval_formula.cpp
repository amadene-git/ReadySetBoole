#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include <stack>
#include <sstream>

#define BOOL 1
#define OP 2


typedef struct s_node
{
    struct s_node   *left;
    struct s_node   *right;
    unsigned int    value;
    char            data;
    unsigned int    type;
}               t_node;

t_node *new_node()
{
    t_node *new_node = (t_node*)malloc(sizeof(t_node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = 0;
    new_node->data = 0;
    new_node->type = 0;
    return (new_node);
}

void    gendot(int *ncount, std::stringstream &dotf, t_node *root, int id)
{
        if (root->type == BOOL)
            dotf << "  node" << id << " [label=\"" << root->data << "\"]\n";
        else if (root->data == '!')
            dotf << "  node" << id << " [label=\"" << root->data << root->left->value << " -> " << root->value << "\"]\n";
        else 
            dotf << "  node" << id << " [label=\"" << root->left->value << root->data << root->right->value << " -> " << root->value << "\"]\n";

        if (root->left != NULL)
        {
            *ncount += 1;
            dotf << "  node" << id << " -> node" << *ncount << "\n";
            gendot(ncount, dotf, root->left, *ncount);
        }
        if (root->right != NULL)
        {
            *ncount += 1;
            dotf << "  node" << id << " -> node" << *ncount << "\n";
            gendot(ncount, dotf, root->right, *ncount);
        }
}


void    print_btree(t_node *root)
{
    std::stringstream dotf;
    dotf << "digraph astgraph {\n\
  node [shape=none, fontsize=12, fontname=\"Courier\", height=.1];\n\
  ranksep=.5;\n\
  edge [arrowsize=.5]\n\n";

    int ncount = 0;
    gendot(&ncount, dotf, root, 0);
    dotf << "\n\n}";
    
    std::stringstream tmp;
    tmp << "echo '" << dotf.str() << "' > tmp.dot";
    
    system(tmp.str().c_str());
    system("rm -rf tree.png;");
    system("dot -Tpng -o tree.png tmp.dot");
    system("rm -rf tmp.dot");
    system("xdg-open tree.png 2> /dev/null");
}


t_node  *make_tree(char *expr)
{
    std::stack<t_node*> my_stack;
    
    for (int i = 0; expr[i] != 0; i++)
    {
        t_node *curr =  new_node();
        curr->data = expr[i];
        if (expr[i] == '0' || expr[i] == '1')
        {
            curr->value = expr[i] - '0'; 
            curr->type = BOOL;
        }
        else
        {
            curr->type = OP;
            curr->left = my_stack.top();
            my_stack.pop();
            if (expr[i] != '!')
            {
                curr->right = my_stack.top();
                my_stack.pop();
            }
            if (expr[i] == '&')    
                curr->value = curr->left->value & curr->right->value; 
            else if (expr[i] == '|')    
                curr->value = curr->left->value | curr->right->value; 
            else if (expr[i] == '!')    
                curr->value = !curr->left->value; 
            else if (expr[i] == '^')    
                curr->value = curr->left->value ^ curr->right->value; 
            // else if (expr[i] == '>')    
            //     curr->value = curr->left->value > curr->right->value; 
            else if (expr[i] == '=')    
                curr->value = curr->left->value == curr->right->value; 

        }
        my_stack.push(curr);
    }
    return (my_stack.top());
}

void    clean_tree(t_node *root)
{

    if (root->left != NULL)
        clean_tree(root->left);
    if (root->right != NULL)
        clean_tree(root->right);

    free(root);

}

bool    eval_formula(char *str)
{
    t_node *tree = make_tree(str);
    bool ret = (bool)tree->value;

   print_btree(tree);

    clean_tree(tree);
  
    return (ret);
}


int main(int ac, char **av)
{

    
    printf("%s\n", (eval_formula(av[1]) == 1 ? "True" : "False"));
}
