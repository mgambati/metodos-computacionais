cmake_minimum_required(VERSION 3.10)
project(metodos_comp_cmake)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2  -Werror")
add_executable(metodos_comp_cmake main.cpp formula_parser.cpp formula_parser.h TokenRepository.cpp TokenRepository.h)