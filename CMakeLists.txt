cmake_minimum_required(VERSION 3.5)
project(metodos_comp)

set(CMAKE_CXX_STANDARD 11)

add_executable(metodos_comp main.cpp formula_parser.cpp formula_parser.h token_helper.cpp token_helper.h zero_of_function.cpp zero_of_function.h termcolor.hpp)

set_target_properties(metodos_comp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)