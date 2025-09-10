find_package(Boost REQUIRED COMPONENTS unit_test_framework)


add_executable(testToken TestToken.cpp)
target_link_libraries(testToken
	btree
)
add_test(NAME test_token COMMAND testToken)
