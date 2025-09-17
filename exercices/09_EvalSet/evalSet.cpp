#include <09_EvalSet/evalSet.h>
#include <stack>

std::vector<int> makeResultSet(std::vector<int>& globalSet,
                               BytesSet& resultBytes) {

  std::vector<int> resultSet;
  for (int i = 0; i < globalSet.size(); ++i) {
    if (resultBytes._bytes[i / 8] & (1 << i % 8)) {
      resultSet.push_back(globalSet[i]);
    }
  }
  return resultSet;
}
std::vector<int> makeGlobalSet(std::vector<std::vector<int>>& sets) {
  std::vector<int> globalSet;
  for (auto& subset : sets) {
    for (auto& elem : subset) {
      if (std::find(globalSet.begin(), globalSet.end(), elem) ==
          globalSet.end()) {
        globalSet.push_back(elem);
      }
    }
  }
  return globalSet;
}

std::vector<BytesSet> makeBytesSets(std::vector<int>& globalSet,
                                    std::vector<std::vector<int>>& sets) {
  std::vector<BytesSet> bytesSets;

  for (auto& subset : sets) {
    bytesSets.push_back(BytesSet{globalSet, subset});
  }
  return bytesSets;
}

std::vector<int> eval_set(std::string str, std::vector<std::vector<int>> sets) {
  auto globalSet = makeGlobalSet(sets);
  std::vector<BytesSet> bytesSets = makeBytesSets(globalSet, sets);
  std::stack<BytesSet> formula;

  for (int i = 0; str[i]; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      formula.push(bytesSets[str[i] - 'A']);
    } else if (str[i] == '!' && formula.size() >= 1)
      formula.top().NOT();
    else if (formula.size() >= 2) {
      auto tmp = formula.top();
      formula.pop();

      if (str[i] == '&')
        formula.top().AND(tmp);
      else if (str[i] == '|')
        formula.top().OR(tmp);
      else if (str[i] == '^')
        formula.top().XOR(tmp);
      else if (str[i] == '>')
        formula.top().IMPLY(tmp);
      else if (str[i] == '=')
        formula.top().EQUAL(tmp);
      else {
        throw std::runtime_error("Error eval_formula(): Invalid formula");
      }
    } else {
      throw std::runtime_error("Error eval_formula(): Invalid formula");
    }
  }

  if (formula.size() != 1) {
    throw std::runtime_error("Error eval_formula(): Invalid formula");
  }
  return makeResultSet(globalSet, formula.top());
}
