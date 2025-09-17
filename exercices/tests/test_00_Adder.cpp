#define BOOST_TEST_MODULE EXERCICE_00_ADDER
#include <00_Adder/adder.h>
#include <boost/test/included/unit_test.hpp>
#include <chrono>

BOOST_AUTO_TEST_CASE(basic_test) {
  BOOST_CHECK(adder(0, 0) == 0);
  BOOST_CHECK(adder(1, 0) == 1);
  BOOST_CHECK(adder(0, 1) == 1);
  BOOST_CHECK(adder(1, 1) == 2);
  BOOST_CHECK(adder(2, 2) == 4);
  BOOST_CHECK(adder(5, 7) == 12);
  BOOST_CHECK(adder(15, 27) == 42);
  BOOST_CHECK(adder(100, 250) == 350);
  BOOST_CHECK(adder(1001, 1002) == 2003);
  BOOST_CHECK(adder(1002, 1001) == 2003);
  BOOST_CHECK(adder(12345, 0) == 12345);
  BOOST_CHECK(adder(0, 67890) == 67890);
  BOOST_CHECK(adder(7, 9) == adder(9, 7));
}

BOOST_AUTO_TEST_CASE(limite_test) {
  auto uintMax = std::numeric_limits<uint32_t>::max();
  BOOST_CHECK(adder(uintMax, 0) == uintMax);
  BOOST_CHECK(adder(0, uintMax) == uintMax);
  BOOST_CHECK(adder(1, uintMax - 1) == uintMax);
}

BOOST_AUTO_TEST_CASE(loop_test) {
  srand(time(NULL));
  for (int i = 0; i < 200 && i >= 0; i++) {
    uint32_t a = (uint32_t)rand() % 2147483648;
    uint32_t b = (uint32_t)rand() % 2147483648;

    BOOST_CHECK_EQUAL(adder(a, b), a + b);
  }
}

BOOST_AUTO_TEST_CASE(overflow_test) {
  try {
    adder(std::numeric_limits<uint32_t>::max(), 1);
    BOOST_CHECK_MESSAGE(false, "no exception thrown");
  } catch (std::overflow_error& e) {
    BOOST_CHECK_EQUAL(e.what(), "adder() overflow");
  }
}

// BOOST_AUTO_TEST_CASE(time_complexity_test) {
//   using namespace std::chrono;

//   unsigned int max = std::numeric_limits<unsigned int>::max() / 2;

//   auto test = [&](unsigned int a, unsigned int b) {
//     auto start = high_resolution_clock::now();
//     for (int i = 0; i < 1000000;
//          ++i) { // 1 million d'exécutions pour lisser la mesure
//       adder(a, b);
//     }
//     auto end = high_resolution_clock::now();
//     return duration_cast<microseconds>(end - start).count();
//   };

//   long t1 = test(1, 1);                 // très petites valeurs
//   // long t2 = test(max, max);             // très grandes valeurs
//   long t2 = test(max * 2, 1);             // très grandes valeurs
//   long t3 = test(123456789, 987654321); // valeurs aléatoires

//   std::cout << "Temps petits nombres  : " << t1 << " ms\n";
//   std::cout << "Temps grands nombres  : " << t2 << " ms\n";
//   std::cout << "Temps aléatoires      : " << t3 << " ms\n";

//   // Vérification empirique : ils doivent être du même ordre de grandeur
//   if (abs(t1 - t2) < t1 * 0.2 && abs(t2 - t3) < t2 * 0.2) {
//     std::cout << "Complexité O(1) respectée ✅\n";
//   } else {
//     std::cout << "Attention : le temps semble dépendre des valeurs ❌\n";
//   }
// }
