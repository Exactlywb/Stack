# cmake_minimum_required(VERSION <specify CMake version here>)
project(stack_clion)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_clion main.cpp stack_lib.h stack_lib_functions.cpp)