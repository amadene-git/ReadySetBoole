
#define BOOST_TEST_MODULE EXERCICE_09_EVAL_SET
#include <boost/test/included/unit_test.hpp>

#include <09_EvalSet/evalSet.h>

BOOST_AUTO_TEST_CASE(makeGlobalSet_test) {
  std::vector<std::vector<int>> sets({{1, 2, 3}, {1, 4}, {1, 2, 3, 5}});
  auto globalSets = makeGlobalSet(sets);
  BOOST_CHECK_EQUAL(globalSets.size(), 5);
}

BOOST_AUTO_TEST_CASE(BytesSet_setBit_test) {
  std::vector<int> globalSet({1, 2, 3, 4});
  std::vector<int> set({4});

  BytesSet bytesSet(globalSet, set);
  //   bytesSet.printBytes();
}

// BOOST_AUTO_TEST_CASE(makeBytesSets_test) {
//   std::vector<std::vector<int>> sets({{1, 2, 3}, {1, 4}, {1, 2, 3, 5}});
//   auto globalSet = makeGlobalSet(sets);

//   auto bytesSets = makeBytesSets(globalSet, sets);

//   for (auto i : bytesSets) {
//     i.printBytes();
//   }
// }

BOOST_AUTO_TEST_CASE(evalSet_test) {
  std::vector<std::vector<int>> sets({{1, 2, 3}, {1, 4}, {1, 2, 3, 5}});
  auto result = eval_set("AB&", sets);

  std::cout << "{";
  for (auto i : result) {
    std::cout << i << ", ";
  }
  std::cout << "}" << std::endl;
}

BOOST_AUTO_TEST_CASE(test) {
  {
    std::vector<std::vector<int>> sets(
        {{1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}, {1}});
    auto result = eval_set("ABCDEFGHIJ&&&&&&&&&", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets({{1, 2},
                                        {1, 3},
                                        {1, 4},
                                        {1, 5},
                                        {1, 6},
                                        {1, 7},
                                        {1, 8},
                                        {1, 9},
                                        {1, 10},
                                        {1, 11}});
    auto result = eval_set("ABCDEFGHIJ&&&&&&&&&", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets({{1, 2},
                                        {1, 3},
                                        {1, 4},
                                        {1, 5},
                                        {1, 6},
                                        {1, 7},
                                        {1, 8},
                                        {1, 9},
                                        {1, 10},
                                        {1, 11},
                                        {0}});
    auto result = eval_set("ABCDEFGHIJK&&&&&&&&&&", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets({{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}});
    auto result = eval_set("ABCDEFGHIJK&&&&&&&&&&", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets({{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {}});
    auto result = eval_set("AB|", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets;

    for (int i = 0; i < 26; ++i) {
      sets.push_back({1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                      14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26});
    }
    auto result =
        eval_set("ABCDEFGHIJKLMNOPQRSTUVWXYZ&&&&&&&&&&&&&&&&&&&&&&&&&", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
  {
    std::vector<std::vector<int>> sets({{1, 2}, {1, 3}});

    auto result = eval_set("AB^", sets);

    std::cout << "{";
    for (auto i : result) {
      std::cout << i << ", ";
    }
    std::cout << "}" << std::endl;
  }
}
