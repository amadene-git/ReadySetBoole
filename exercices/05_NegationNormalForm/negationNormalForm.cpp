#include <05_NegationNormalForm/negationNormalForm.h>

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


NegationNormalForm *make_NNF_tree(Node *root)
{
    NegationNormalForm *node = NULL;
    NegationNormalForm *left = NULL;
    NegationNormalForm *right = NULL;

    if (root->left)
        left = make_NNF_tree(root->left);
    if (root->right)
        right = make_NNF_tree(root->right);
    
    node = new NegationNormalForm(root->data, root->str, root->type, left, right, root->value);    
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


std::string  negation_normal_form(char *str)
{
    Node *tree = make_tree(str);
    if (!tree)
        return ("");

    NegationNormalForm *nnftree = make_NNF_tree(tree);
    if (!nnftree)
        return ("");
    std::string ret = treetostr(nnftree);

    clean_tree(tree);
    clean_tree(nnftree);

    return (ret);
}




