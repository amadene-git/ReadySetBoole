#include <vector>

#include "eval_formula.hpp"

int main()
{
	std::vector<std::pair<std::string, bool>> resultsTab = {
		{"0!", true},
		{"1!", false},

		{"00&", false},
		{"10&", false},
		{"01&", false},
		{"11&", true},

		{"00|", false},
		{"10|", true},
		{"01|", true},
		{"11|", true},

		{"00^", false},
		{"10^", true},
		{"01^", true},
		{"11^", false},

		{"00>", true},
		{"10>", false},
		{"01>", true},
		{"11>", true},

		{"00=", true},
		{"10=", false},
		{"01=", false},
		{"11=", true}};

	for (auto it : resultsTab)
	{
		if (eval_formula(const_cast<char *>(it.first.c_str())) != it.second)
		{
			std::cerr << "\033[31m" << "Test failed: \033[0m" << it.first << " expected return "
					  << std::boolalpha << it.second << std::endl;
		}
		else
		{
			std::cout << "\033[32m" << "Test passed: \033[0m" << it.first.c_str() << " <===> "
					  << std::boolalpha << it.second << std::endl;
		}
	}
}