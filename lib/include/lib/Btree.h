#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <04_TruthTable/printTruthTable.h>
#include <lib/Node.h>
#include <vector>


Node *make_tree(char *expr);

template <typename T>
T *dup_tree(T *root)
{
	T *node = new T(*root);

	if (root->left != nullptr)
		node->left = dup_tree(root->left);
	if (root->right != nullptr)
		node->right = dup_tree(root->right);

	return (node);
}

template <typename T>
void clean_tree(T *root)
{
	if (!root)
		return;
	if (root->left != nullptr)
		clean_tree(root->left);
	if (root->right != nullptr)
		clean_tree(root->right);

	delete root;
}

template <typename T>
std::string treetostr(T *root)
{
	std::string str;

	if (root && root->left)
		str += treetostr(root->left);
	if (root && root->right)
		str += treetostr(root->right);

	str += std::string(1, root->data);

	return (str);
}

template <typename T>
void print_postfix(T *root)
{
	if (!root)
		return;
	if (root->left != nullptr)
		print_postfix(root->left);
	if (root->right != nullptr)
		print_postfix(root->right);
	std::cout << root->data;
}

template <typename T>
void print_btree(T *root, std::string filename = "tree.png")
{
	std::stringstream dotf;
	std::string str = treetostr(root);

	std::cout << "**** Print BTree postfix ****\n"
			  << str << std::endl;
	std::cout << "\n" + std::string(29, '*') << std::endl;
	std::cout << "**** Print BTree truthtable ****" << std::endl;
	print_truth_table(str);
	std::cout << std::string(32, '*') << std::endl;

	dotf << "digraph astgraph {\n\
    node [shape=box, fontsize=12, fontname=\"Courier\", height=.1, style=filled];\n\
    ranksep=.5;\n\
    edge [dir=both, arrowsize=.5, arrowhead=none]\n\n";

	int ncount = 0;
	gendot(&ncount, dotf, root, 0);
	dotf << "\n\n}";

	std::stringstream tmp;
	tmp << "echo '" << dotf.str() << "' > tmp.dot";

	system(tmp.str().c_str());
	system(std::string("rm -rf " + filename).c_str());
	system(std::string("dot -Tpng -o " + filename + " tmp.dot").c_str());
	system("rm -rf tmp.dot");
	system(std::string("xdg-open " + filename + " 2> /dev/nullptr").c_str());
}

template <typename T>
void gendot(int *ncount, std::stringstream &dotf, T *root, int id)
{
	if (root->type == BOOL)
	{
		dotf << "node" << id << " [label=\"" << root->data << "\"]\n";
	}
	else if (root->value == -1)
	{
		dotf << "node" << id << " [label=\"" << root->data << "     " << root->str << "\"]\n";
	}
	else
		dotf << "node" << id << " [label=\"" << root->value << "    " << root->str << "\"]\n";
	if (root->value == 0)
		dotf << "node" << id << "[color=\"red\"]\n";
	else if (root->value == 1)
		dotf << "node" << id << "[color=\"green\"]\n";

	if (root->left != nullptr)
	{
		*ncount += 1;
		dotf << "node" << id << " -> node" << *ncount << "\n";
		gendot(ncount, dotf, root->left, *ncount);
	}
	if (root->right != nullptr)
	{
		*ncount += 1;
		dotf << "node" << id << " -> node" << *ncount << "\n";
		gendot(ncount, dotf, root->right, *ncount);
	}
}
