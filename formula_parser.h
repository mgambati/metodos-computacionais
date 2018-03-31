#ifndef METODOS_COMP_CMAKE_FORMULA_PARSER_H
#define METODOS_COMP_CMAKE_FORMULA_PARSER_H

#include <string>

using namespace std;

bool IsDigitOrDot(char c);

bool OpHasHigherPrecedence(char first, char second);

string FindNumberOrFuncInString(string expr, int from_position, int *ends_in);

queue<string> ParseExpression(string expr);

#endif //METODOS_COMP_CMAKE_FORMULA_PARSER_H
