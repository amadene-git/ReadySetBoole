#include "readysetboole.h"

Node    *exit_error(vector<Node*> &stk, string mes = "")
{
    while (stk.size())
    {
        delete stk.back();
        stk.pop_back();
    }
    cerr << mes << endl;
    return(NULL);
}

Node  *make_tree(char *expr)
{
    vector<Node*> stk;
    vector<Node*> garbage;
    Node *curr =  NULL;


    for (int i = 0; expr[i] != 0; i++)
    {
        curr =  new Node(expr[i]);
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
                        
            curr->type = NOT;
            curr->left = stk.back();
            stk.pop_back();

            curr->str = "!(" + curr->left->str + ")"; 
            if (curr->left->value != -1)
                curr->value = !curr->left->value;
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
            {    
                curr->type = AND;
                curr->str = "(" + curr->left->str + " & " + curr->right->str + ")";
                if (curr->left->value != -1 && curr->right->value  != -1)
                    curr->value = curr->left->value & curr->right->value; 
            }
            else if (expr[i] == '|')
            {    
                curr->type = OR;
                curr->str = "(" + curr->left->str + " | " + curr->right->str + ")";
                if (curr->left->value != -1 && curr->right->value  != -1)
                    curr->value = curr->left->value | curr->right->value; 
            }
            else if (expr[i] == '^')
            {    
                curr->type = XOR;
                curr->str = "(" + curr->left->str + " ^ " + curr->right->str + ")";
                if (curr->left->value != -1 && curr->right->value  != -1)
                    curr->value = curr->left->value ^ curr->right->value; 
            }
            else if (expr[i] == '>')
            {    
                curr->type = IMPLY;
                curr->str = "(" + curr->left->str + " > " + curr->right->str + ")";
                if (curr->left->value != -1 && curr->right->value  != -1)
                    curr->value = (!curr->left->value) | (curr->right->value);// p=>q <=> (!p)|q
            }
            else if (expr[i] == '=')
            {    
                curr->type = EQUAL;
                curr->str = "(" + curr->left->str + " = " + curr->right->str + ")";
                if (curr->left->value != -1 && curr->right->value  != -1)
                    curr->value = curr->left->value == curr->right->value; 
            }
        }
        else
            return (exit_error(garbage, "Error: bad character"));
        stk.push_back(curr);
    }
    if (stk.size() != 1)
        return (exit_error(garbage, "Error: too much boolean"));
   
        
    return (stk.back());
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

bool    eval_formula(char *str)
{


    Node *tree = make_tree(str);
    if (tree == NULL)
        return (false);

    bool ret = (bool)tree->value;
    print_btree(tree);
    print_postfix(tree);
    cout << endl;
    clean_tree(tree);  
    return (ret);


    return (simple_eval(str));
}
