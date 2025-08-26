#ifndef NNF_HPP
# define NNF_HPP

# include "Btree.hpp"

class NNF : public Node
{
    public:
        NNF(char data = 0, string str = "", int type = -1, NNF *left = NULL, NNF *right = NULL, int value = -1)
        {
            this->data = data;
            this->str = str;
            this->type = type;
            this->left = left;
            this->right = right;
            this->value = value;
        };

        NNF(NNF const &rhs)
        {
            // cout << "NNF Copy constructor called -> " << this << endl;
            *this = rhs;
        };
        
        NNF& operator=(NNF const &rhs)
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

        NNF operator!()
        {
            NNF ret = *this;
            
            // cout << "NNF operation: NOT " << this << endl;
            if (this->type == NOT)// !!A = A
            {
                ret = *this->left;
                delete this->left;
            }
            else if (this->type == AND)// !(A & B) -> !A | !B;
            {
                NNF *A = new NNF(!*this->left);
                NNF *B = new NNF(!*this->right);
                ret = *A | *B;
            }
            else if (this->type == OR)// !(A | B) -> !A & !B;
            {
                NNF *A = new NNF(!*this->left);
                NNF *B = new NNF(!*this->right);
                ret = *A & *B;
            }
            else
            {
                // cout << "NNF operation: NOT " << this << endl;
                ret.type = NOT;
                ret.data = '!';
                ret.left = this;
                ret.right = NULL;
                ret.str = "!" + this->str;
                if (this->value != -1)
                    ret.value = !(this->value);
                
                return (ret);
            }
            
            delete this;
            return (ret);
        };
        NNF operator|(NNF const &rhs)
        {
            NNF ret;

            // cout << "NNF operation: OR " << this << " | " << &rhs << endl;
            ret.type = OR;
            ret.data = '|';
            ret.left = this;
            ret.right = (NNF*)&rhs;
            ret.str = "(" + this->str + " | " + rhs.str + ")";
            if (this->value != -1 && rhs.value != -1)
                ret.value = this->value | rhs.value;

            return (ret);
        };
        NNF operator&(NNF const &rhs)
        {
            NNF ret;

            // cout << "NNF operation: AND " << this << " & " << &rhs << endl;
            ret.type = AND;
            ret.data = '&';
            ret.left = this;
            ret.right = (NNF*)&rhs;
            ret.str = "(" + this->str + " & " + rhs.str + ")";
            if (this->value != -1 && rhs.value != -1)
                ret.value = this->value & rhs.value;

            return (ret);
        };
        NNF operator^(NNF &rhs)// A ^ B -> (!A &  B )  |  ( A & !B )
        {
            NNF ret;
            NNF *A = new NNF( *(new NNF(!*dup_tree(this))) & rhs );
            NNF *B = new NNF( *this   & *(new NNF(!*dup_tree(&rhs))) );
            ret = *A | *B;

            return (ret);
        };
        NNF operator>(NNF &rhs)//    A > B  ->  !A |  B 
        {
            // cout << "NNF operation: IMPY " << this << " > " << &rhs << endl;
            NNF ret;
            NNF *A = new NNF(!*this);
            ret = *A | rhs;

            return (ret);
        };        
        NNF operator==(NNF &rhs)// A = B  -> ( A &  B )  |  (!A & !B )
        {
            NNF ret;
            NNF *A = new NNF( *this & rhs );
            NNF *B = new NNF(*(new NNF(!*dup_tree(this))) & *(new NNF(!*dup_tree(&rhs))));
            ret = *A | *B;

            return (ret);
        };

        ~NNF() {};

        NNF *left;
        NNF *right;
};


#endif