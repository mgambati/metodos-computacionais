//
// Created by mgambati on 04/04/18.
//

#include <string>
#include <unordered_map>
#include "TokenRepository.h"

using namespace std;


unordered_map<string, int> TokenRepository::op_info{
        {"+", 2},
        {"-", 2},
        {"/", 3},
        {"*", 3},
        {"^", 4},
};

unordered_map<string, int> TokenRepository::fn_info{
        {"(",   1},
        {")",   1},
        {"cos", 1},
        {"sin", 1},
        {"log", 1},
        {"ln",  1},
        {"tg",  1}
};

unordered_map<string, int> TokenRepository::const_info{
        {"e",  1},
        {"pi", 1},
};

bool TokenRepository::IsTokenOp(string *token) {
    return TokenRepository::op_info.count(*token) > 0;
}

bool TokenRepository::IsTokenFn(string *token) {
    return TokenRepository::fn_info.count(*token) > 0;
}

bool TokenRepository::IsTokenConst(string *token) {
    return TokenRepository::const_info.count(*token) > 0;
}

int TokenRepository::GetOpPrecedence(string token) {
    return TokenRepository::op_info[token];
};

bool TokenRepository::OpHasHigherPrecedence(string first, string second) {
    return TokenRepository::GetOpPrecedence(first) > TokenRepository::GetOpPrecedence(second);
}