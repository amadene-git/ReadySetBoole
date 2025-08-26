#pragma once

#include <iostream>
#include <string>

#include <lib/Btree.h>


std::string  negation_normal_form(char *str);

class NegationNormalForm : public Node
{
public:
	NegationNormalForm(char data = 0, std::string str = "", int type = -1, NegationNormalForm *left = NULL, NegationNormalForm *right = NULL, int value = -1)
	{
		this->data = data;
		this->str = str;
		this->type = type;
		this->left = left;
		this->right = right;
		this->value = value;
	};

	NegationNormalForm(NegationNormalForm const &rhs)
	{
		// cout << "NegationNormalForm Copy constructor called -> " << this << endl;
		*this = rhs;
	};

	NegationNormalForm &operator=(NegationNormalForm const &rhs)
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

	NegationNormalForm operator!()
	{
		NegationNormalForm ret = *this;

		// cout << "NegationNormalForm operation: NOT " << this << endl;
		if (this->type == NOT) // !!A = A
		{
			ret = *this->left;
			delete this->left;
		}
		else if (this->type == AND) // !(A & B) -> !A | !B;
		{
			NegationNormalForm *A = new NegationNormalForm(!*this->left);
			NegationNormalForm *B = new NegationNormalForm(!*this->right);
			ret = *A | *B;
		}
		else if (this->type == OR) // !(A | B) -> !A & !B;
		{
			NegationNormalForm *A = new NegationNormalForm(!*this->left);
			NegationNormalForm *B = new NegationNormalForm(!*this->right);
			ret = *A & *B;
		}
		else
		{
			// cout << "NegationNormalForm operation: NOT " << this << endl;
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
	NegationNormalForm operator|(NegationNormalForm const &rhs)
	{
		NegationNormalForm ret;

		// cout << "NegationNormalForm operation: OR " << this << " | " << &rhs << endl;
		ret.type = OR;
		ret.data = '|';
		ret.left = this;
		ret.right = (NegationNormalForm *)&rhs;
		ret.str = "(" + this->str + " | " + rhs.str + ")";
		if (this->value != -1 && rhs.value != -1)
			ret.value = this->value | rhs.value;

		return (ret);
	};
	NegationNormalForm operator&(NegationNormalForm const &rhs)
	{
		NegationNormalForm ret;

		// cout << "NegationNormalForm operation: AND " << this << " & " << &rhs << endl;
		ret.type = AND;
		ret.data = '&';
		ret.left = this;
		ret.right = (NegationNormalForm *)&rhs;
		ret.str = "(" + this->str + " & " + rhs.str + ")";
		if (this->value != -1 && rhs.value != -1)
			ret.value = this->value & rhs.value;

		return (ret);
	};
	NegationNormalForm operator^(NegationNormalForm &rhs) // A ^ B -> (!A &  B )  |  ( A & !B )
	{
		NegationNormalForm ret;
		NegationNormalForm *A = new NegationNormalForm(*(new NegationNormalForm(!*dup_tree(this))) & rhs);
		NegationNormalForm *B = new NegationNormalForm(*this & *(new NegationNormalForm(!*dup_tree(&rhs))));
		ret = *A | *B;

		return (ret);
	};
	NegationNormalForm operator>(NegationNormalForm &rhs) //    A > B  ->  !A |  B
	{
		// cout << "NegationNormalForm operation: IMPY " << this << " > " << &rhs << endl;
		NegationNormalForm ret;
		NegationNormalForm *A = new NegationNormalForm(!*this);
		ret = *A | rhs;

		return (ret);
	};
	NegationNormalForm operator==(NegationNormalForm &rhs) // A = B  -> ( A &  B )  |  (!A & !B )
	{
		NegationNormalForm ret;
		NegationNormalForm *A = new NegationNormalForm(*this & rhs);
		NegationNormalForm *B = new NegationNormalForm(*(new NegationNormalForm(!*dup_tree(this))) & *(new NegationNormalForm(!*dup_tree(&rhs))));
		ret = *A | *B;

		return (ret);
	};

	~NegationNormalForm() {};

	NegationNormalForm *left;
	NegationNormalForm *right;
};
