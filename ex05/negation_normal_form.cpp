#include "readysetboole.h"

/*
    !!A ->  A

    !(A & B)    -> !A | !B
    !(A | B)    -> !A & !B
    
    !(A > B)    ->   A & !B         
    !(A ^ B)    -> ( A | !B )  &  (!A |  B )
    !(A = B)    -> ( A |  B )  &  (!A | !B)
    
    A > B       ->  !A |  B         
    A ^ B       -> (!A &  B )  |  ( A & !B )
    A = B       -> ( A &  B )  |  (!A & !B )
                
*/


CNF *make_CNF_tree(Node *root)
{
    CNF *node = NULL;
    CNF *left = NULL;
    CNF *right = NULL;
    // CNF *tmp = NULL;


    if (root->left)
        left = make_CNF_tree(root->left);
    if (root->right)
        right = make_CNF_tree(root->right);
    
    node = new CNF(root->data, root->str, root->type, left, right, root->value);
    
    if (node->type == NOT) 
        *node = !*node->left;
    else if (node->type == XOR)
        *node = *node->left ^ *node->right;
    // else if (node->type == IMPLY)
    //     *node = *node->left > *node->right;
    // else if (node->type == EQUAL)
    //     *node = *node->left == *node->right;
    
    return (node);
}


string  negation_normal_form(char *str)
{
    Node *tree = make_tree(str);
    if (!tree)
        return ("");

    print_btree<Node>(tree, "tree.png");

    CNF *cnftree = make_CNF_tree(tree);

    print_btree<CNF>(cnftree, "cnftree.png");

    string ret = treetostr(cnftree);

    vector<void*> garbage;
    clean_tree(tree, garbage);
    clean_tree(cnftree, garbage);

    return (ret);
}




