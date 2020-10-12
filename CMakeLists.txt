cmake_minimum_required(VERSION 3.17)
project(stack_last_version)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_last_version main.cpp MyStack.h stack_lib.cpp)