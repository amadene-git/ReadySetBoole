## Btree
add_library(btree
    src/Token.cpp
    src/Node.cpp
)
target_include_directories(btree PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(btree
truthTable
) #########################################################


add_library(bytesSet
    src/BytesSet.cpp
)
target_include_directories(bytesSet PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bytesSet
) #########################################################


enable_testing()
add_subdirectory(test)
