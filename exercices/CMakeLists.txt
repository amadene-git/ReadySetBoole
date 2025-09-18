## Adder ##################################################
add_library(adder
    00_Adder/adder.cpp
)
target_include_directories(adder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


## Multiplier #############################################
add_library(multiplier
    01_Multiplier/multiplier.cpp
)
target_include_directories(multiplier PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(multiplier
	adder
)


## GrayCode ###############################################
add_library(grayCode
    02_GrayCode/grayCode.cpp
)
target_include_directories(grayCode PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


## BooleanEvaluation ######################################
add_library(booleanEvaluation
    03_BooleanEvaluation/evalFormula.cpp
)
target_include_directories(booleanEvaluation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(booleanEvaluation
	btree
)
add_executable(mainTestBooleanEvaluation  03_BooleanEvaluation/main.cpp)
target_link_libraries(mainTestBooleanEvaluation
   booleanEvaluation
)


## PrintTruthTable ########################################
add_library(truthTable
    04_TruthTable/printTruthTable.cpp
)
target_include_directories(truthTable PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(truthTable
	booleanEvaluation
)


## NegationNormalForm #####################################
add_library(negationNormalForm
    05_NegationNormalForm/negationNormalForm.cpp
)
target_include_directories(negationNormalForm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(negationNormalForm
	PUBLIC	
	btree
)


## ConjunctiveNormalForm #####################################
add_library(conjunctiveNormalForm
    06_ConjunctiveNormalForm/conjunctiveNormalForm.cpp
)
target_include_directories(conjunctiveNormalForm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(conjunctiveNormalForm
	PUBLIC	
	negationNormalForm
)


## SAT #####################################
add_library(SAT
    07_SAT/sat.cpp
)
target_include_directories(SAT PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(SAT
	PUBLIC	
	truthTable
)

## Powerset #####################################
add_library(powerset
    08_Powerset/powerset.cpp
)
target_include_directories(powerset PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(powerset
	PUBLIC
	bytesSet	
)

## evalSet #####################################
add_library(evalSet
    09_EvalSet/evalSet.cpp
)
target_include_directories(evalSet PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(evalSet
	PUBLIC	
	powerset
)

find_package(Boost COMPONENTS unit_test_framework)
if(Boost_FOUND)
    enable_testing()
    add_subdirectory(tests)
else()
    message(WARNING "Boost non trouvé. tests désactivées.")
endif()


