#include "readysetboole.h"

ConjunctiveNormalForm *make_ConjunctiveNormalForm_tree(NNF *root)
{
    ConjunctiveNormalForm *node = NULL;
    ConjunctiveNormalForm *left = NULL;
    ConjunctiveNormalForm *right = NULL;

    if (root->left)
        left = make_ConjunctiveNormalForm_tree(root->left);
    if (root->right)
        right = make_ConjunctiveNormalForm_tree(root->right);
    
    node = new ConjunctiveNormalForm(root->data, root->str, root->type, left, right, root->value);    
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
    ConjunctiveNormalForm *ConjunctiveNormalFormtree = make_ConjunctiveNormalForm_tree(nnftree);
    
    print_btree<ConjunctiveNormalForm>(ConjunctiveNormalFormtree);


    string ret = treetostr(ConjunctiveNormalFormtree);
    clean_tree<Node>(tree);
    clean_tree<NNF>(nnftree);
    clean_tree<ConjunctiveNormalForm>(ConjunctiveNormalFormtree);

    return (ret);
}