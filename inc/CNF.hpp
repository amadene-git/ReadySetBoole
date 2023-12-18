#ifndef CNF_HPP
# define CNF_HPP

# include "Node.hpp"

template <typename T>
void    print_btree(T *root, string filename = "tree.png");


class CNF : public Node
{
    public:
        CNF(char data = 0, string str = "", int type = -1, CNF *left = NULL, CNF *right = NULL, int value = -1)
        {
            this->data = data;
            this->str = str;
            this->type = type;
            this->left = left;
            this->right = right;
            this->value = value;
        };

        CNF(CNF const &rhs)
        {
            cout << "CNF Copy constructor called -> " << this << endl;
            *this = rhs;
        };
        
        CNF& operator=(CNF const &rhs)
        {
            if (&rhs != this)
            {
                this->left = rhs.left;
                this->right = rhs.right;
                this->value = rhs.value;
                this->type = rhs.type;
                this->str = rhs.str;
                this->data = rhs.data;
            }
            return (*this);
        };
        
        
        CNF operator!()
        {
            CNF ret = *this;
            
            cout << "CNF operation: NOT " << this << endl;
            if (this->type == NOT)// !!A = A
            {
                cout << "NOT VAR " << this << endl;
                ret = *this->left;
                // delete this->left;
            }
            else if (this->type == AND)// !(A & B) -> !A | !B;
            {
                CNF *A = new CNF(!*this->left);
                CNF *B = new CNF(!*this->right);
                ret = *A | *B;
                
            }
            else if (this->type == OR)// !(A | B) -> !A & !B;
            {
                CNF *A = new CNF(!*this->left);
                CNF *B = new CNF(!*this->right);
                ret = *A & *B;
                
            }
            else
            {

                cout << "CNF operation: NOT " << this << endl;
                ret.type = NOT;
                ret.data = '!';
                ret.left = this;
                ret.right = NULL;
                ret.str = "!" + this->str;
                if (this->value != -1)
                    ret.value = !(this->value);
                
                return (ret);
            }
            
            // delete this;
            return (ret);
        };
        CNF operator|(CNF const &rhs)
        {
            CNF ret;

            cout << "CNF operation: OR " << this << " | " << &rhs << endl;
            ret.type = OR;
            ret.data = '|';
            ret.left = this;
            ret.right = (CNF*)&rhs;
            ret.str = "(" + this->str + " | " + rhs.str + ")";
            if (this->value != -1 && rhs.value != -1)
                ret.value = this->value | rhs.value;
            
            return (ret);
        };
        CNF operator&(CNF const &rhs)
        {
            CNF ret;

            cout << "CNF operation: AND " << this << " & " << &rhs << endl;
            ret.type = AND;
            ret.data = '&';
            ret.left = this;
            ret.right = (CNF*)&rhs;
            ret.str = "(" + this->str + " & " + rhs.str + ")";
            if (this->value != -1 && rhs.value != -1)
                ret.value = this->value & rhs.value;
            
            return (ret);
        };
        CNF operator^(CNF &rhs)// A ^ B -> (!A &  B )  |  ( A & !B )
        {
            CNF ret;

            CNF *A = new CNF( *(new CNF(!*(new CNF(*this)))) & *(new CNF(rhs)));
            CNF *B = new CNF( *(new CNF(*this))   & *(new CNF(!*(new CNF(rhs)))));
            
            ret = *(new CNF(*A | *B));
            // delete this;
            // delete &rhs;
            
            return (ret);

        };

        ~CNF() {};

        CNF *left;
        CNF *right;
};


#endif