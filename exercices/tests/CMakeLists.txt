find_package(Boost REQUIRED COMPONENTS unit_test_framework)


## 00
add_executable(testAdder test_00_Adder.cpp)
target_link_libraries(testAdder
    PRIVATE
    Boost::unit_test_framework
	adder
)
add_test(NAME 00_Adder COMMAND testAdder)

## 01
add_executable(testMultiplier test_01_Multiplier.cpp)
target_link_libraries(testMultiplier
    PRIVATE
    Boost::unit_test_framework
	multiplier
)
add_test(NAME 01_Multiplier COMMAND testMultiplier)

## 02
add_executable(testGrayCode test_02_GrayCode.cpp)
target_link_libraries(testGrayCode
    PRIVATE
    Boost::unit_test_framework
	grayCode
)
add_test(NAME 02_GrayCode COMMAND testGrayCode)

## 03
add_executable(testBooleanEvaluation test_03_BooleanEvaluation.cpp)
target_link_libraries(testBooleanEvaluation
    PRIVATE
    Boost::unit_test_framework
	booleanEvaluation
)
add_test(NAME 03_BooleanEvaluation COMMAND testBooleanEvaluation)

## 04
add_executable(testTruthTable test_04_TruthTable.cpp)
target_link_libraries(testTruthTable
    PRIVATE
    Boost::unit_test_framework
	truthTable
)
add_test(NAME 04_TruthTable COMMAND testTruthTable)

## 05
add_executable(testNegationNormalForm test_05_NegationNormalForm.cpp)
target_link_libraries(testNegationNormalForm
    PRIVATE
    Boost::unit_test_framework
	negationNormalForm
)
add_test(NAME 05_NegationNormalForm COMMAND testNegationNormalForm)
