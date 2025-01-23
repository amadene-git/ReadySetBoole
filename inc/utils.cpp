#include "readysetboole.h"

/////////////////////////////////////////////////////////
//********************* BTree *************************//
/////////////////////////////////////////////////////////

Node *exit_error(vector<Node *> &stk, string mes = "")
{
    while (stk.size())
    {
        delete stk.back();
        stk.pop_back();
    }
    cerr << mes << endl;
    return (NULL);
}

Node *make_tree(char *expr)
{
    vector<Node *> stk;
    vector<Node *> garbage;
    Node *curr = NULL;

    for (int i = 0; expr[i] != 0; i++)
    {
        curr = new Node(expr[i]);
        garbage.push_back(curr);

        if (expr[i] == '0' || expr[i] == '1')
        {
            curr->type = BOOL;
            if (expr[i] == '1')
                curr->str = "1";
            if (expr[i] == '0')
                curr->str = "0";
            curr->value = expr[i] - '0';
        }
        else if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            curr->type = VAR;
            curr->value = -1;
            curr->str = string(1, expr[i]);
        }
        else if (expr[i] == '!')
        {
            if (stk.size() < 1)
                return (exit_error(garbage, "Error: not enough operands"));

            *curr = !(*stk.back());
            stk.pop_back();
        }
        else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=')
        {
            if (stk.size() < 2)
                return (exit_error(garbage, "Error: not enough boolean"));

            curr->right = stk.back();
            stk.pop_back();
            curr->left = stk.back();
            stk.pop_back();

            if (expr[i] == '&')
                *curr = *curr->left & *curr->right;
            else if (expr[i] == '|')
                *curr = *curr->left | *curr->right;
            else if (expr[i] == '^')
                *curr = *curr->left ^ *curr->right;
            else if (expr[i] == '>')
                *curr = *curr->left > *curr->right;
            else if (expr[i] == '=')
                *curr = *curr->left == *curr->right;
        }
        else
            return (exit_error(garbage, "Error: bad character"));
        stk.push_back(curr);
    }
    if (stk.size() != 1)
        return (exit_error(garbage, "Error: too much boolean"));

    return (stk.back());
}
