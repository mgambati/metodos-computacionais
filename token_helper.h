//
// Created by mathe on 05/04/2018.
//

#ifndef METODOS_COMP_CMAKE_TOKEN_HELPER_H
#define METODOS_COMP_CMAKE_TOKEN_HELPER_H

#include <string>
#include <map>
#include <cmath>

using namespace std;

struct TokenInfo {
    int precedence;
    bool left_associative;
};

extern map<string, TokenInfo> op_info;

bool IsTokenOp(string token);

bool IsTokenFn(string token);

bool IsTokenConst(string token);

int GetOpPrecedence(string token);

int GetOpLeftAssociativity(string token);

double GetConstValue(string token);

bool CompareOpPrecedenceOrLA(string first, string second);

string SearchForNonNumericToken(string expr, int from_position, int *ends_in);

string SearchForNumericToken(string expr, int from_position, int *ends_in);

string SearchForToken(string expr, int from_position, int *ends_in, bool *is_number);

#endif //METODOS_COMP_CMAKE_TOKEN_HELPER_H
