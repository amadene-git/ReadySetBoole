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


NNF *make_NNF_tree(Node *root)
{
    NNF *node = NULL;
    NNF *left = NULL;
    NNF *right = NULL;

    if (root->left)
        left = make_NNF_tree(root->left);
    if (root->right)
        right = make_NNF_tree(root->right);
    
    node = new NNF(root->data, root->str, root->type, left, right, root->value);    
    if (node->type == NOT) 
        *node = !*node->left;
    else if (node->type == XOR)
        *node = *node->left ^ *node->right;
    else if (node->type == IMPLY)
        *node = *node->left > *node->right;
    else if (node->type == EQUAL)
        *node = *node->left == *node->right;

    return (node);
}


string  negation_normal_form(char *str)
{
    Node *tree = make_tree(str);
    if (!tree)
        return ("");

    NNF *nnftree = make_NNF_tree(tree);
    if (!nnftree)
        return ("");
    string ret = treetostr(nnftree);

    clean_tree(tree);
    clean_tree(nnftree);

    return (ret);
}




