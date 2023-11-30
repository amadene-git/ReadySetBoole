#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>
#include <stack>
#include <sstream>


typedef struct s_node
{
    struct s_node   *left;
    struct s_node   *right;
    char              value;
}               t_node;

t_node *new_node(int value)
{
    t_node *new_node = (t_node*)malloc(sizeof(t_node));
    new_node->value = value;

    return (new_node);
}


void    gendot(int *ncount, std::stringstream &dotf, t_node *root, int id)
{
        dotf << "  node" << id << " [label=\"" << root->value << "\"]\n";


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
    // system("rm -rf tmp.dot");
    system("xdg-open tree.png 2> /dev/null");
}


int main()
{
    char expr[] = "101|&";
    std::stack<t_node*> my_stack;
    
    for (int i = 0; expr[i] != 0; i++)
    {
        t_node *curr =  new_node(expr[i]); 
        if (expr[i] == '&' || expr[i] == '|')
        {
            curr->right = my_stack.top();
            my_stack.pop();
            
            curr->left = my_stack.top();
            my_stack.pop();
        }
        my_stack.push(curr);
    }

    print_btree(my_stack.top());
    
    printf("%s\n", expr);
}
