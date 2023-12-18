#ifndef BTREE_HPP
# define BTREE_HPP

class Node;
class CNF;

#include "Node.hpp"
#include "CNF.hpp"





template <typename T>
void    clean_tree(T *root, vector<void*> &garbage)
{
    if (!root)
        return;
    if (root->left != NULL)
        clean_tree(root->left, garbage);
    if (root->right != NULL)
        clean_tree(root->right, garbage);
    
    if (find(garbage.begin(), garbage.end(), (void*)root) == garbage.end())
    {
        
    delete root;
    garbage.push_back((void*)root);
    }
    // else
    // {
    //     cout << "FOUND " << endl;
    // }
}


template <typename T>
string treetostr(T *root)
{    
    string str;
    
    if (root && root->left)
        str += treetostr(root->left);
    if (root && root->right)
        str += treetostr(root->right);
    
    str += string(1, root->data);

    return (str);

}

template <typename T>
void    print_postfix(T *root)
{
    if (!root)
        return;
    if (root->left != NULL)
        print_postfix(root->left);
    if (root->right != NULL)
        print_postfix(root->right);
    cout << root->data;
}

template <typename T>
void    print_btree(T *root, string filename)
{
    stringstream dotf;
    string str = treetostr(root);

    cout << "**** Print BTree postfix ****\n" << str << endl;
    cout << "\n" + string(29, '*') << endl;
    cout << "**** Print BTree truthtable ****" << endl;
    print_truth_table(str);
    cout << string(32, '*') << endl;
    
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
    system(string("rm -rf " + filename).c_str());
    system(string("dot -Tpng -o " + filename + " tmp.dot").c_str());
    system("rm -rf tmp.dot");
    system(string("xdg-open " + filename + " 2> /dev/null").c_str());
}

template <typename T>
void    gendot(int *ncount, std::stringstream &dotf, T *root, int id)
{
        if (root->type == BOOL)
        {
            dotf << "node" << id << " [label=\"" << root->data << "\"]\n";
        }
        else if (root->value == -1)
        {
            dotf << "node" << id << " [label=\"" << root->data << "     " << root->str << "\"]\n";
        }
        else 
            dotf << "node" << id << " [label=\"" << root->value << "    " << root->str << "\"]\n";
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




#endif