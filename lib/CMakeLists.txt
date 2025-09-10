## Btree
add_library(btree
    src/Token.cpp
    src/AMANode.cpp
)
target_include_directories(btree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(btree
truthTable
) #########################################################


enable_testing()
add_subdirectory(test)
