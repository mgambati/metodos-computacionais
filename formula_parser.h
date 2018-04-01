#ifndef METODOS_COMP_CMAKE_FORMULA_PARSER_H
#define METODOS_COMP_CMAKE_FORMULA_PARSER_H

#include <string>

using namespace std;

stack<string> ParseExpressionToRPN(string expr);

#endif //METODOS_COMP_CMAKE_FORMULA_PARSER_H
