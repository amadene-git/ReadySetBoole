#pragma once
#include <08_Powerset/powerset.h>
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> makeGlobalSet(std::vector<std::vector<int>>& sets);

std::vector<BytesSet> makeBytesSets(std::vector<int>& globalSet,
                                    std::vector<std::vector<int>>& sets);

std::vector<int> eval_set(std::string formula,
                          std::vector<std::vector<int>> sets);
