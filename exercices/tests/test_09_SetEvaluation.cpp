
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
  ;
}
