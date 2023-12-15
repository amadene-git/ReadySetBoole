#include "readysetboole.h"

/*
    !!A ->  A 

    !(A & B)    -> !A | !B
    !(A | B)    -> !A & !B
    
    A > B       -> !A  |   B         
    !(A > B)    ->  A  &  !B         

    A ^ B       -> (!A &  B )  |  ( A & !B )
    !(A ^ B)    -> ( A | !B )  &  (!A |  B )

    A = B       -> ( A & B )  |  (!A & !B )
    !(A = B)    -> (!A | !B)  &  ( A |  B )
                
*/


// Node  *tresmake_tree(string expr)
// {
//     stack<Node*> stk;
//     stack<Node*> garbage;
//     Node *curr =  NULL;
//     Node *tmp =  NULL;

//     for (int i = 0; expr[i] != 0; i++)
//     {
//         curr =  new_node();
//         garbage.push(curr);
//         curr->data = expr[i];
//         if (expr[i] >= 'A' && expr[i] <= 'Z')
//         {
//             curr->type = BOOL;
//             curr->value = 0;
//         }
//         else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=' || expr[i] == '!')
//         {   
//             if (expr[i] == '!') 
//             {
//                 if (stk.size() < 1)
//                     bisexit_error(garbage, "Error: not enough operands");
                
//                 curr->type = OP;
//                 curr->left = stk.top();
//                 stk.pop();
//             }
//             else if (expr[i] == '^')
//             {
//                 tmp = new_node();
//                 tmp->right = stk.top();
//                 stk.pop();                 
//                 tmp->left = stk.top();
//                 stk.pop();                 
                
//                                                       //////////////////////////////////
//                 curr->data = '|';// <<=============== // A ^ B -> (!A & B) | (A & !B) //
//                 curr->type = OP;                      //////////////////////////////////
//                                                       //              |         |     //
//                                                       //              |         |     //
//                                                       //              V         |     //
//                 curr->left = new_node();// <---------------------(!A  &  B)     |     //
//                 curr->left->data = '&';               //           |     |      |     //
//                 curr->left->type = OP;                //           |     |      |     //
//                                                       //           |     |      |     //
//                 curr->left->left = new_node();// <----------------!A     |      |     //
//                 curr->left->left->data = '!';         //                 |      |     //
//                 curr->left->left->type = OP;          //                 |      |     //
//                 curr->left->left->left = tmp->left;   //                 |      |     //
//                 curr->left->right = tmp->right;// <----------------------B      |     //
//                                                       //                        |     //
//                                                       //                        |     //
//                                                       //                        V     //
//                 curr->right = new_node();// <-------------------------------(A  & !B) //
//                 curr->right->data = '&';              //                     |     |  //
//                 curr->right->type = OP;               //                     |     |  //
//                                                       //                     |     |  //
//                 curr->right->left = tmp->left;// <---------------------------A     |  //
//                                                       //                           |  //
//                 curr->right->right = new_node();      //                           |  //
//                 curr->right->right->data = '!';       //                           |  //
//                 curr->right->right->type = OP;        //                           |  //
//                 curr->right->right->left = tmp->right;// <------------------------!B  //
//                                                       //////////////////////////////////
//             }
//             else if (expr[i] == '=')
//             {
//                 tmp = new_node();
//                 tmp->right = stk.top();
//                 stk.pop();                 
//                 tmp->left = stk.top();
//                 stk.pop();                 
                

//                                                       //////////////////////////////////
//                 curr->data = '|';// <<=============== // A = B -> (A & B) | (!A & !B) //
//                 curr->type = OP;                      ////////////////////////////////// 
//                                                       //             |          |     //
//                                                       //             |          |     //
//                                                       //             |          |     //
//                                                       //             V          |     //
//                 curr->left = new_node();// <---------------------(A  &  B)      |     //
//                 curr->left->data = '&';               //          |     |       |     //
//                 curr->left->type = OP;                //          |     |       |     //
//                                                       //          |     |       |     //
//                 curr->left->left = tmp->left;// <-----------------A     |       |     //
//                 curr->left->right = tmp->right;// <---------------------B       |     //
//                                                       //                        |     //
//                                                       //                        |     //
//                                                       //                        V     //
//                 curr->right = new_node();// <------------------------------(!A  & !B) //
//                 curr->right->data = '&';              //                    |      |  //
//                 curr->right->type = OP;               //                    |      |  //
//                                                       //                    |      |  //
//                 curr->right->left = new_node();       //                    |      |  //
//                 curr->right->left->data = '!';        //                    |      |  //
//                 curr->right->left->type = OP;         //                    |      |  //
//                 curr->right->left->left = tmp->left;// <--------------------A      |  //
//                                                       //                           |  //
//                 curr->right->right = new_node();      //                           |  //
//                 curr->right->right->data = '!';       //                           |  //
//                 curr->right->right->type = OP;        //                           |  //
//                 curr->right->right->left = tmp->right;// <----------------------- !B  //
//                                                       //////////////////////////////////
//             }
//             else
//             {
//                 if (stk.size() < 2)
//                     bisexit_error(garbage, "Error: not enough boolean");
                
//                 curr->type = OP;
//                 curr->right = stk.top();
//                 stk.pop();
//                 curr->left = stk.top();
//                 stk.pop();
//             }
//         }
//         else
//             bisexit_error(garbage, "Error: bad character");
//         if (curr)
//             stk.push(curr);
//     }
    
//     if (stk.size() != 1)
//         bisexit_error(garbage, "Error: too much boolean");
        
//     return (stk.top());
// }


// Node  *bismake_tree(string expr)
// {
//     stack<Node*> stk;
//     stack<Node*> garbage;
//     Node *curr =  NULL;
//     Node *tmp =  NULL;

//     for (int i = 0; expr[i] != 0; i++)
//     {
//         curr =  new_node();
//         garbage.push(curr);
//         curr->data = expr[i];
//         if (expr[i] >= 'A' && expr[i] <= 'Z')
//         {
//             curr->type = BOOL;
//             curr->value = 0;
//         }
//         else if (expr[i] == '&' || expr[i] == '|' || expr[i] == '^' || expr[i] == '>' || expr[i] == '=' || expr[i] == '!')
//         {   
//             if (expr[i] == '!') 
//             {
//                 if (stk.size() < 1)
//                     bisexit_error(garbage, "Error: not enough operands");
                
//                 if (stk.top()->data == '!' && stk.top()->left)
//                 {
//                     free(curr);
//                     curr = stk.top()->left;
//                     free(stk.top());
//                     stk.pop();
//                 }
//                 else if (stk.top()->data == '|')
//                 {
//                     tmp = new_node();//!A
//                     tmp->data = '!';
//                     tmp->type = OP;
//                     tmp->left = stk.top()->left;
//                     curr->left = tmp;

//                     tmp = new_node();//!B
//                     tmp->data = '!';
//                     tmp->type = OP;
//                     tmp->left = stk.top()->right;
//                     curr->right = tmp;

//                                         /////////////////////////
//                     curr->data = '&';   // !(A | B) -> !A & !B //
//                                         /////////////////////////
//                     free(stk.top());
//                     stk.pop();
//                 }
//                 else if (stk.top()->data == '&')
//                 {
//                     tmp = new_node();//!A
//                     tmp->data = '!';
//                     tmp->type = OP;
//                     tmp->left = stk.top()->left;
//                     curr->left = tmp;

//                     tmp = new_node();//!B
//                     tmp->data = '!';
//                     tmp->type = OP;
//                     tmp->left = stk.top()->right;
//                     curr->right = tmp;

//                                         /////////////////////////
//                     curr->data = '|';   // !(A & B) -> !A | !B //
//                                         /////////////////////////
                    
//                     free(stk.top());
//                     stk.pop();
//                 }
//                 else
//                 {
//                     curr->type = OP;
//                     curr->left = stk.top();
//                     stk.pop();
//                 }
//             }
//             else
//             {
//                 if (stk.size() < 2)
//                     bisexit_error(garbage, "Error: not enough boolean");
                
//                 curr->type = OP;
//                 curr->right = stk.top();
//                 stk.pop();
//                 curr->left = stk.top();
//                 stk.pop();
//             }
//         }
//         else
//             bisexit_error(garbage, "Error: bad character");
//         if (curr)
//             stk.push(curr);
//     }
    
//     if (stk.size() != 1)
//         bisexit_error(garbage, "Error: too much boolean");
        
//     return (stk.top());
// }


Node *make_negtree(Node *root)
{
    Node *node = NULL;
    Node *left = NULL;
    Node *right = NULL;
    Node *tmp = NULL;
    
    if (root->left)
        left = make_negtree(root->left);
    if (root->right)
        right = make_negtree(root->right);
    
    node = new Node(root->data, root->str, root->type, left, right, root->value);
            cout <<  node << "   tmp str " << node->str << endl;
    if (node->type == NOT)
    {
        if (node->left->type == NOT)// !!A -> A
        {
            tmp = node->left->left;
            delete node->left;
            delete node;
            node = tmp;
            cout <<  node << "  ---->>>> tmp str " << node->str << endl;
        }
        else if (node->left->type == AND)//!(A & B)    -> !A | !B
        {
            node->right = new Node('!', "!("+node->left->right->str+")", NOT, node->left->right, NULL,\
            (node->left->right->value != -1) ? !node->left->right->value : -1);
            
            node->left->data  = '!'; 
            node->left->type  = NOT;
            node->left->str   = "!(" + left->left->str + ")";
            node->left->left  = left->left;
            node->left->right = NULL;
            


            node->type = OR;
            node->data = '|';
            node->str = "(" + node->left->str + " | " + node->right->str + ")";
            
            if (node->left->value != -1 && node->right->value != -1)
                node->value = node->left->value | node->right->value;

        }
        else if (node->left->type == OR)//!(A | B)    -> !A & !B
        {
            node->right = new Node('!', "!("+node->left->right->str+")", NOT, node->left->right, NULL,\
            (node->left->right->value != -1) ? !node->left->right->value : -1);
            
            node->left->data  = '!'; 
            node->left->type  = NOT;
            node->left->str   = "!(" + left->left->str + ")";
            node->left->left  = left->left;
            node->left->right = NULL;
            


            node->type = AND;
            node->data = '&';
            node->str = "(" + node->left->str + " & " + node->right->str + ")";
            
            if (node->left->value != -1 && node->right->value != -1)
                node->value = node->left->value & node->right->value;

        }

        else//!A = !A
        {
            node->str = "!(" + node->left->str + ")";
            node->data = '!';
            if (node->value != -1)
                node->value = !node->value;
        }
    
    }
    else if (node->type == IMPLY)// A ^ B -> !A | B
    {
        cout << "WESHHHHH" << endl;
        node->type = OR;
        node->data = '|';
        node->left = new Node('!', "!("+root->left->str+")", NOT, left, NULL, (left->value != -1) ? !left->value : -1);
        node->str = "(" + node->left->str + " | " + node->right->str + ")";
        if (node->left->value != -1 && node->right->value != -1)
            node->value = node->left->value | node->right->value;
    }
    // else if 
    return (node);
}



string  negation_normal_form(char *str)
{
    Node *tree = make_tree(str);
    if (!tree)
        return ("Error");
    
    Node *ntree = make_negtree(tree);
    
    
    cout << "HERE "<< ntree << endl;
    
    
    clean_tree(tree);

    print_btree(ntree);
    string ret = ntree->str;

    clean_tree(ntree);
    return (ret);

}




