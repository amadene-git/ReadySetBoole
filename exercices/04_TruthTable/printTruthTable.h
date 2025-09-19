#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>

#include <03_BooleanEvaluation/evalFormula.h>

std::string str_truth_table(std::string formula);
void print_truth_table(const std::string& formula);

void createOperands(std::map<char, bool>& operands, std::string formula);
void updateOperands(std::map<char, bool>& operands, uint32_t value);
void printOperandsSymbol(std::map<char, bool>& operands);
void printOperandsAndResultValue(std::map<char, bool>& operands, int result);
std::string convertOperandsSymbolToBool(std::map<char, bool> operands,
                                        std::string formulaCopy);
