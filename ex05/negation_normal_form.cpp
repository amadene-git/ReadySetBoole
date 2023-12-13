#include "readysetboole.h"

/*
    A   ->  A
    !A  -> !A
    !!A ->  A 

    !(A | B) -> !A & !B
    !(A & B) -> !A | !B

    A ^ B -> (!A & B) | (A & !B)
    
    !(A ^ B) -> !( (!A & B) |  (A & !B) )
             ->   !(!A & B) & !(A & !B)  
             ->   (!!A | !B) & (!A | !!B) 
    ---------->     (A | !B) & (!A | B)  


    A > B       -> !A  |   B         
    !(A > B)    ->  A  &  !B         


    A = B       -> (A & B) | (!A & !B)

    !(A = B)    -> !((A & B) | (!A & !B))
                -> !(A & B) & !(!A & !B)
                -> (!A | !B) & (A | B)

    
    

ABC|&!      !((B | C) & A)
A!          !(B | C) | !A
            (!B & !C) | !A
    
    A!B!C!&|
    B!C!&A!|


*/

void    bisexit_error(stack<t_node*> stk, string mes = "")
{
    while (stk.size())
    {
        free(stk.top());
        stk.pop();
    }
    cerr << mes << endl;
    exit(1);
}

t_node  *tresmake_tree(string expr)
{
    stack<t_node*> stk;
    stack<t_node*> garbage;
    t_node *curr =  NULL;
    t_node *tmp =  NULL;

    for (int i = 0; expr[i] != 0; i++)
    {
        curr =  new_node();
        garbage.push(curr);
        curr->data = expr[i];
        if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            curr->type = BOOL;
            curr->value = 0;
        }
        else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=' || expr[i] == '!')
        {   
            if (expr[i] == '!') 
            {
                if (stk.size() < 1)
                    bisexit_error(garbage, "Error: not enough operands");
                
                curr->type = OP;
                curr->left = stk.top();
                stk.pop();
            }
            else if (expr[i] == '^')
            {
                tmp = new_node();
                tmp->right = stk.top();
                stk.pop();                 
                tmp->left = stk.top();
                stk.pop();                 
                
                                                  //////////////////////////////////
                curr->data = '|';                 // A ^ B -> (!A & B) | (A & !B) //
                curr->type = OP;                  //////////////////////////////////
                                                      //          |         |
                                                      //          |         |
                                                      //          V         |
                curr->left = new_node();// <-----------------(!A  &  B)     |
                curr->left->data = '&';               //       |     |      |
                curr->left->type = OP;                //       |     |      |
                                                      //       |     |      |
                curr->left->left = new_node();// <------------!A     |      |
                curr->left->left->data = '!';         //             |      |
                curr->left->left->type = OP;          //             |      |
                curr->left->left->left = tmp->left;   //             |      |
                curr->left->right = tmp->right;// <------------------B      |
                                                      //                    |
                                                      //                    |
                                                      //                    V
                curr->right = new_node();// <---------------------------(A  & !B)
                curr->right->data = '&';              //                 |     |
                curr->right->type = OP;               //                 |     |
                                                      //                 |     |
                curr->right->left = tmp->left;// <-----------------------A     |
                                                      //                       |
                curr->right->right = new_node();      //                       |
                curr->right->right->data = '!';       //                       |
                curr->right->right->type = OP;        //                       |
                curr->right->right->left = tmp->right;// <--------------------!B
                
            }
            else if (expr[i] == '=')
            {
                tmp = new_node();
                tmp->right = stk.top();
                stk.pop();                 
                tmp->left = stk.top();
                stk.pop();                 
                

                                                   //////////////////////////////////
                curr->data = '|';// <------------- // A = B -> (A & B) | (!A & !B) //
                curr->type = OP;                   ////////////////////////////////// 
                                                      //          |          |
                                                      //          |          |
                                                      //          |          |
                                                      //          V          |
                curr->left = new_node();// <------------------(A  &  B)      |
                curr->left->data = '&';               //       |     |       |
                curr->left->type = OP;                //       |     |       |
                                                      //       |     |       |
                curr->left->left = tmp->left;// <--------------A     |       |
                curr->left->right = tmp->right;// <------------------B       |
                                                      //                     |
                                                      //                     |
                                                      //                     V
                curr->right = new_node();// <---------------------------(!A  & !B)
                curr->right->data = '&';              //                 |      |
                curr->right->type = OP;               //                 |      |
                                                      //                 |      |
                curr->right->left = new_node();       //                 |      |
                curr->right->left->data = '!';        //                 |      |
                curr->right->left->type = OP;         //                 |      |
                curr->right->left->left = tmp->left;// <-----------------A      |
                                                      //                        |
                curr->right->right = new_node();      //                        |
                curr->right->right->data = '!';       //                        |
                curr->right->right->type = OP;        //                        |
                curr->right->right->left = tmp->right;// <-------------------- !B
                
            }
            else
            {
                if (stk.size() < 2)
                    bisexit_error(garbage, "Error: not enough boolean");
                
                curr->type = OP;
                curr->right = stk.top();
                stk.pop();
                curr->left = stk.top();
                stk.pop();
            }
        }
        else
            bisexit_error(garbage, "Error: bad character");
        if (curr)
            stk.push(curr);
    }
    
    if (stk.size() != 1)
        bisexit_error(garbage, "Error: too much boolean");
        
    return (stk.top());
}


t_node  *bismake_tree(string expr)
{
    stack<t_node*> stk;
    stack<t_node*> garbage;
    t_node *curr =  NULL;
    t_node *tmp =  NULL;

    for (int i = 0; expr[i] != 0; i++)
    {
        curr =  new_node();
        garbage.push(curr);
        curr->data = expr[i];
        if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            curr->type = BOOL;
            curr->value = 0;
        }
        else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=' || expr[i] == '!')
        {   
            if (expr[i] == '!') 
            {
                if (stk.size() < 1)
                    bisexit_error(garbage, "Error: not enough operands");
                
                if (stk.top()->data == '!' && stk.top()->left)
                {
                    free(curr);
                    curr = stk.top()->left;
                    free(stk.top());
                    stk.pop();
                }
                else if (stk.top()->data == '|')
                {
                    tmp = new_node();//!A
                    tmp->data = '!';
                    tmp->type = OP;
                    tmp->left = stk.top()->left;
                    curr->left = tmp;

                    tmp = new_node();//!B
                    tmp->data = '!';
                    tmp->type = OP;
                    tmp->left = stk.top()->right;
                    curr->right = tmp;

                                        /////////////////////////
                    curr->data = '&';   // !(A | B) -> !A & !B //
                                        /////////////////////////
                    free(stk.top());
                    stk.pop();
                }
                else if (stk.top()->data == '&')
                {
                    tmp = new_node();//!A
                    tmp->data = '!';
                    tmp->type = OP;
                    tmp->left = stk.top()->left;
                    curr->left = tmp;

                    tmp = new_node();//!B
                    tmp->data = '!';
                    tmp->type = OP;
                    tmp->left = stk.top()->right;
                    curr->right = tmp;

                                        /////////////////////////
                    curr->data = '|';   // !(A & B) -> !A | !B //
                                        /////////////////////////
                    
                    free(stk.top());
                    stk.pop();
                }
                else
                {
                    curr->type = OP;
                    curr->left = stk.top();
                    stk.pop();
                }
            }
            else
            {
                if (stk.size() < 2)
                    bisexit_error(garbage, "Error: not enough boolean");
                
                curr->type = OP;
                curr->right = stk.top();
                stk.pop();
                curr->left = stk.top();
                stk.pop();
            }
        }
        else
            bisexit_error(garbage, "Error: bad character");
        if (curr)
            stk.push(curr);
    }
    
    if (stk.size() != 1)
        bisexit_error(garbage, "Error: too much boolean");
        
    return (stk.top());
}


void    btreetostr_post(t_node *root, string &ret)
{
    if (root->left)
        btreetostr_post(root->left, ret);
    if (root->right)
        btreetostr_post(root->right, ret);
    ret += root->data;

}



string  negation_normal_form(char *str)
{
    string s(str);
    string  tmp;
    t_node *root;
    root = tresmake_tree(s);
    print_btree(root);
    s.clear();
    btreetostr_post(root, s);

    while (tmp != s)
    {
        tmp = s;
        root = bismake_tree(s);
        // print_btree(root);
        s.clear();
        btreetostr_post(root, s);

    }
    print_btree(root);

    // clean_tree(root);
    return (s);

}




