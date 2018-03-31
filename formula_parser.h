#ifndef METODOS_COMP_CMAKE_FORMULA_PARSER_H
#define METODOS_COMP_CMAKE_FORMULA_PARSER_H

#include <string>

using namespace std;

bool IsDigitOrDot(char c);

string FindNumberInString(string expr, int *from_position);

queue<string> ParseExpression(string expr);

#endif //METODOS_COMP_CMAKE_FORMULA_PARSER_H
