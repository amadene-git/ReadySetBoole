#include "Btree.hpp"

class CNF : public NNF
{
  
    public:

    ~CNF(){};
    CNF(char data = 0, string str = "", int type = -1, CNF *left = NULL, CNF *right = NULL, int value = -1)
    {
        this->data = data;
        this->str = str;
        this->type = type;
        this->left = left;
        this->right = right;
        this->value = value;
    };
    CNF(CNF const &copy)
    {
        *this = copy;
    };
    CNF& operator=(CNF const &rhs)
    {
        // cout << "CNF equal operation: " << this << " = " << &rhs << endl;
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
    

    CNF operator&(CNF const &rhs)
    {
        CNF ret;
        if (this->str == rhs.str)
        {
            ret = *this;
            clean_tree<CNF>((CNF*)&rhs);
            delete this;
        }
        else
        {
            ret.type = AND;
            ret.data = '&';
            ret.left = this;
            ret.right = (CNF*)&rhs;
            ret.str = "(" + this->str + " & " + rhs.str + ")";
            if (this->value != -1 && rhs.value != -1)
                ret.value = this->value & rhs.value;
        }
        return (ret);
    };
    CNF *left;
    CNF *right;

};