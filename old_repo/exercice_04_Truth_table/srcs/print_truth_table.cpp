#include "print_truth_table.hpp"

std::string str_truth_table(std::string formula)
{
	bool alpha[26] = {0};
	std::vector<int> var;
	std::string tmp;
	std::string str;

	for (int i = 0; i < (int)formula.length(); i++)
		if (formula[i] >= 'A' && formula[i] <= 'Z')
			alpha[formula[i] - 'A'] = 1;

	for (int i = 0; i < 26; i++)
		if (alpha[i])
			var.push_back(i);

	for (int i = 0; i < (1 << (int)var.size()); i++)
	{
		bzero(alpha, sizeof(alpha));
		tmp.clear();

		for (int j = 0; j <= (int)var.size(); j++)
			if (((i >> j) & 1) == 1)
				alpha[var.size() - j - 1] = 1;

		tmp = formula;
		for (int j = 0; j < (int)var.size(); j++)
			replace(tmp.begin(), tmp.end(), var[j] + 'A', alpha[var[j]] + '0');

		str += eval_formula((char *)tmp.c_str()) + '0';
	}
	return (str);
}

void print_truth_table(std::string formula)
{
	bool alpha[26] = {0};
	std::vector<int> var;
	std::string tmp;

	for (int i = 0; i < (int)formula.length(); i++)
		if (formula[i] >= 'A' && formula[i] <= 'Z')
			alpha[formula[i] - 'A'] = 1;

	for (int i = 0; i < 26; i++)
		if (alpha[i])
			var.push_back(i);

	for (int i = 0; i < (int)var.size(); i++)
		std::cout << "| " << char(var[i] + 'A') << " ";
	std::cout << "| = |" << std::endl;

	for (int i = 0; i < (1 << (int)var.size()); i++)
	{
		bzero(alpha, sizeof(alpha));
		tmp.clear();

		for (int j = 0; j <= (int)var.size(); j++)
			if (((i >> j) & 1) == 1)
				alpha[var.size() - j - 1] = 1;

		tmp = formula;
		for (int j = 0; j < (int)var.size(); j++)
			replace(tmp.begin(), tmp.end(), var[j] + 'A', alpha[var[j]] + '0');

		for (int i = 0; i < (int)var.size(); i++)
			std::cout << "| " << alpha[var[i]] << " ";
		std::cout << "| " << eval_formula((char *)tmp.c_str()) << " |" << std::endl;
	}
}