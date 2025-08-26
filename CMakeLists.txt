cmake_minimum_required(VERSION 3.10)
project(MonProjet)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

# Ajouter les sous-répertoires
add_subdirectory(lib)
add_subdirectory(exercices)

enable_testing()



