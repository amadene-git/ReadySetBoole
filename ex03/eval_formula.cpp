#include "readysetboole.h"

void    exit_error(stack<t_node*> stk, string mes = "")
{
    while (stk.size())
    {
        free(stk.top());
        stk.pop();
    }
    cerr << mes << endl;
    exit(1);
}

t_node  *make_tree(string expr)
{
    stack<t_node*> stk;
    stack<t_node*> garbage;
    t_node *curr =  NULL;

    for (int i = 0; expr[i] != 0; i++)
    {
        curr =  new_node();
        garbage.push(curr);
        curr->data = expr[i];
        if (expr[i] == '0' || expr[i] == '1')
        {
            curr->type = BOOL;
            curr->value = expr[i] - '0';
        }
        else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=' || expr[i] == '!')
        {   
            if (expr[i] == '!') 
            {
                if (stk.size() < 1)
                    exit_error(garbage, "Error: not enough operands");
                            
                curr->type = OP;
                curr->left = stk.top();
                stk.pop();
    
                curr->value = !curr->left->value;
            }
            else
            {
                if (stk.size() < 2)
                    exit_error(garbage, "Error: not enough boolean");
                
                curr->type = OP;
                curr->right = stk.top();
                stk.pop();
                curr->left = stk.top();
                stk.pop();

                if (expr[i] == '&')    
                    curr->value = curr->left->value & curr->right->value; 
                else if (expr[i] == '|')    
                    curr->value = curr->left->value | curr->right->value; 
                else if (expr[i] == '^')    
                    curr->value = curr->left->value ^ curr->right->value; 
                else if (expr[i] == '>')    
                    curr->value = (!curr->left->value) | (curr->right->value);// p=>q <=> (!p)|q
                else if (expr[i] == '=')    
                    curr->value = curr->left->value == curr->right->value; 
            }
        }
        else
            exit_error(garbage, "Error: bad character");
        stk.push(curr);
    }
    
    if (stk.size() != 1)
        exit_error(garbage, "Error: too much boolean");
        
    return (stk.top());
}


bool    simple_eval(string str)
{
    stack<bool> stk;
    bool        tmp;

    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] == '0')
            stk.push(false);
        else if (str[i] == '1')
            stk.push(true);
        else if (str[i] == '!' && stk.size() >= 1)
            stk.top() = !stk.top();
        else if (str[i] == '&' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() & tmp;
        }
        else if (str[i] == '|' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() | tmp;
        }
        else if (str[i] == '^' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() ^ tmp;
        }
        else if (str[i] == '>' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = (!stk.top()) | tmp;
        }
        else if (str[i] == '=' && stk.size() >= 2)
        {
            tmp = stk.top();
            stk.pop();
            stk.top() = stk.top() == tmp;
        }
        else
        {
            cerr << "Error: Bad character" << endl;
            exit(1);
        }
    }

    if (stk.size() != 1)
    {
            cerr << "Error: invalid formula" << endl;
            exit(1);
    }
    return (stk.top());

}

bool    eval_formula(string str)
{

    return (simple_eval(str));

    // t_node *tree = make_tree(str);
    // if (!tree)
    //     exit_error(stack<t_node*>(), "Error making btree");
    // bool ret = (bool)tree->value;
    // // print_btree(tree);
    // // print_postfix(tree);
    // clean_tree(tree);  
    // return (ret);
}
