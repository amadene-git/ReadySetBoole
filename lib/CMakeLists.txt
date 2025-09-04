## Btree
add_library(btree
    src/Btree.cpp
    src/Node.cpp
)
target_include_directories(btree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(btree
truthTable
) #########################################################
