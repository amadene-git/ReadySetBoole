#include "readysetboole.h"

CNF *make_CNF_tree(NNF *root)
{
    CNF *node = NULL;
    CNF *left = NULL;
    CNF *right = NULL;

    if (root->left)
        left = make_CNF_tree(root->left);
    if (root->right)
        right = make_CNF_tree(root->right);
    
    node = new CNF(root->data, root->str, root->type, left, right, root->value);    
    if (node->type == AND)
        *node = *node->left & *node->right;
    
    // if (node->type == NOT) 
    //     *node = !*node->left;
    // else if (node->type == XOR)
    //     *node = *node->left ^ *node->right;
    // else if (node->type == IMPLY)
    //     *node = *node->left > *node->right;
    // else if (node->type == EQUAL)
    //     *node = *node->left == *node->right;

    return (node);
}


string conjunctive_normal_form(char *formula)
{
    Node *tree = make_tree(formula);
    NNF *nnftree = make_NNF_tree(tree);
    CNF *cnftree = make_CNF_tree(nnftree);
    
    print_btree<CNF>(cnftree);


    string ret = treetostr(cnftree);
    clean_tree<Node>(tree);
    clean_tree<NNF>(nnftree);
    clean_tree<CNF>(cnftree);

    return (ret);
}