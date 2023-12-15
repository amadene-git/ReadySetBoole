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


void    gendot(int *ncount, std::stringstream &dotf, Node *root, int id)
{
        if (root->type == BOOL)
        {
            dotf << "node" << id << " [label=\"" << root->data << "\"]\n";
        }
        else if (root->value == -1)
        {
            dotf << "node" << id << " [label=\"" << root->str << "\"]\n";
        }
        else 
            dotf << "node" << id << " [label=\"" << root->value << "    " << root->data << "\"]\n";
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

void    print_btree(Node *root)
{
    cout << "**** Print BTree postfix ****" << endl;
    print_postfix(root);
    cout << "\n" + string(28, '*') << endl;
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

void    clean_tree(Node *root)
{
    if (!root)
        return;
    if (root->left != NULL)
        clean_tree(root->left);
    if (root->right != NULL)
        clean_tree(root->right);
    delete root;
}

void    print_postfix(Node *root)
{
    if (!root)
        return;
    if (root->left != NULL)
        print_postfix(root->left);
    if (root->right != NULL)
        print_postfix(root->right);
    cout << root->data;
}
