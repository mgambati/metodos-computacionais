//
// Created by mgambati on 04/04/18.
//

#ifndef METODOS_COMP_CMAKE_TOKEN_REPOSITORY_CLASS_H
#define METODOS_COMP_CMAKE_TOKEN_REPOSITORY_CLASS_H

#include <string>
#include <unordered_map>

using namespace std;

class TokenRepository {
public:
    static unordered_map<string, int> op_info;
    static unordered_map<string, int> fn_info;
    static unordered_map<string, int> const_info;

    static bool IsTokenOp(string *token);

    static bool IsTokenFn(string *token);

    static bool IsTokenConst(string *token);

    static int GetOpPrecedence(string token);

    static bool OpHasHigherPrecedence(string first, string second);
};


#endif //METODOS_COMP_CMAKE_TOKEN_REPOSITORY_CLASS_H
