cmake_minimum_required(VERSION 3.5)
project(metodos_comp_cmake)

set(CMAKE_CXX_STANDARD 11)

add_executable(metodos_comp_cmake main.cpp formula_parser.cpp formula_parser.h token_helper.cpp token_helper.h)