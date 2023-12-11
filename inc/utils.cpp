#include "readysetboole.h"

void ft_putnbr_base(uint32_t nb, string base, uint32_t baselen)
{
    int i = 1;
    if (baselen == 0)
    {
        while (uint32_t(1 << i) <= nb && i < 32)
            i++;
        while (i < 32)
        {
            cout << 0;
            i++;
        }
        baselen = base.length();
    }
    if (nb >= baselen)
        ft_putnbr_base(nb / baselen, base, baselen);
    cout << base[nb % baselen];
}



/////////////////////////////////////////////////////////
//********************* BTree *************************//
/////////////////////////////////////////////////////////
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
            dotf << "node" << id << " [label=\"" << root->data << "\"]\n";
        else if (root->data == '!')
            dotf << "node" << id << " [label=\"" << root->value << "    " << root->data << root->left->value << "\"]\n";
        else 
            dotf << "node" << id << " [label=\"" << root->value << "    " << root->left->value << root->data << root->right->value << "\"]\n";
        
        if (root->value == 0)
            dotf << "node" << id << "[color=\"red\"]\n";
        else if (root->value == 1)
            dotf << "node" << id << "[color=\"green\"]\n";
        if (root->left != NULL)
        {
            *ncount += 1;
            dotf << "node" << id << " -> node" << *ncount << "\n";
            gendot(ncount, dotf, root->left, *ncount);
        }
        if (root->right != NULL)
        {
            *ncount += 1;
            dotf << "node" << id << " -> node" << *ncount << "\n";
            gendot(ncount, dotf, root->right, *ncount);
        }
}

void    print_btree(t_node *root)
{
    std::stringstream dotf;
    dotf << "digraph astgraph {\n\
    node [shape=box, fontsize=12, fontname=\"Courier\", height=.1, style=filled];\n\
    ranksep=.5;\n\
    edge [dir=both, arrowsize=.5, arrowhead=none]\n\n";

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

void    clean_tree(t_node *root)
{
    if (!root)
        return;
    if (root->left != NULL)
        clean_tree(root->left);
    if (root->right != NULL)
        clean_tree(root->right);
    free(root);
}

void    print_postfix(t_node *root)
{
    if (!root)
        return;
    if (root->left != NULL)
        print_postfix(root->left);
    if (root->right != NULL)
        print_postfix(root->right);
    cout << root->data;
}
