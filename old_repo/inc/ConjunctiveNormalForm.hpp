#include "Btree.hpp"

class ConjunctiveNormalForm : public NNF {
  public:
  ~ConjunctiveNormalForm() {};
  ConjunctiveNormalForm(char data = 0, string str = "", int type = -1, ConjunctiveNormalForm *left = NULL,
                        ConjunctiveNormalForm *right = NULL, int value = -1) {
    this->data = data;
    this->str = str;
    this->type = type;
    this->left = left;
    this->right = right;
    this->value = value;
  };
  ConjunctiveNormalForm(ConjunctiveNormalForm const &copy) { *this = copy; };
  ConjunctiveNormalForm &operator=(ConjunctiveNormalForm const &rhs) {
    // cout << "ConjunctiveNormalForm equal operation: " << this << " = " << &rhs << endl;
    if (&rhs != this) {
      this->left = rhs.left;
      this->right = rhs.right;
      this->value = rhs.value;
      this->type = rhs.type;
      this->str = rhs.str;
      this->data = rhs.data;
    }
    return (*this);
  };

  ConjunctiveNormalForm operator&(ConjunctiveNormalForm const &rhs) {
    ConjunctiveNormalForm ret;
    if (this->str == rhs.str) {
      ret = *this;
      clean_tree<ConjunctiveNormalForm>((ConjunctiveNormalForm *)&rhs);
      delete this;
    } else {
      ret.type = AND;
      ret.data = '&';
      ret.left = this;
      ret.right = (ConjunctiveNormalForm *)&rhs;
      ret.str = "(" + this->str + " & " + rhs.str + ")";
      if (this->value != -1 && rhs.value != -1)
        ret.value = this->value & rhs.value;
    }
    return (ret);
  };
  ConjunctiveNormalForm *left;
  ConjunctiveNormalForm *right;
};