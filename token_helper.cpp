#include <string>
#include <map>
#include <cmath>
#include "token_helper.h"

using namespace std;

struct TokenInfo;

map<string, TokenInfo> op_info{
        {"+", {2, true}},
        {"-", {2, true}},
        {"/", {3, true}},
        {"*", {3, true}},
        {"^", {4, false}},
};

/**
 * Verifica se a token é um operador
 * @param token
 * @return
 */
bool IsTokenOp(string token) {
    static string op_arr[]{
            "+", "-", "/", "*", "^"
    };

    for (string item : op_arr) {
        if (item == token)
            return true;
    }

    return false;
}

/**
 * Verifica se token é uma função matemática
 * @param token
 * @return
 */
bool IsTokenFn(string token) {
    static string fn_arr[]{
            "(", ")", "cos", "sin", "tg", "log", "ln", "sqrt"
    };

    for (string item : fn_arr) {
        if (item == token)
            return true;
    }

    return false;
}

/**
 * Verifica se token é uma variável
 * @param token
 * @return
 */
bool IsTokenConst(string token) {
    static string const_arr[]{
            "pi", "e"
    };

    for (string item : const_arr) {
        if (item == token)
            return true;
    }

    return false;
}

int GetOpPrecedence(string token) {
    return op_info[token].precedence;
};

int GetOpLeftAssociativity(string token) {
    return op_info[token].left_associative;
};

double GetConstValue(string token) {
    if (token == "pi")
        return M_PI;
    return M_E;
}

/**
 * Retorn true se o first tiver precedencia maior ou é associativo a direita
 * @param first
 * @param second
 * @return
 */
bool CompareOpPrecedenceOrLA(string first, string second) {
    int p_first = GetOpPrecedence(first);
    int p_second = GetOpPrecedence(second);
    bool has_eq_p = p_first == p_second;

    if (has_eq_p)
        return GetOpLeftAssociativity(first);

    return GetOpPrecedence(first) > GetOpPrecedence(second);
}

/**
 * Busca por uma token de função ou operador
 * @param expr
 * @param from_position
 * @param ends_in
 * @return
 */
string SearchForNonNumericToken(string expr, int from_position, int *ends_in) {
    int fn_token_size = 1;
    while (fn_token_size <= 4) {
        string token = expr.substr(from_position, fn_token_size);
        if (IsTokenOp(token) || IsTokenFn(token) || IsTokenConst(token)) {
            *ends_in = from_position + fn_token_size;
            return token;
        }

        fn_token_size++;
    }

    return "";
}

/**
 * Procura por uma token que seja um número, com ou sem ponto flutuante.
 * Ex: 2.22, .343
 * @param expr
 * @param from_position
 * @param ends_in
 * @return
 */
string SearchForNumericToken(string expr, int from_position, int *ends_in) {
    string number = "";

    if (expr[from_position] == 'x') {
        *ends_in = ++from_position;
        return "x";
    }

    while (from_position < expr.length() && isdigit(expr[from_position]) || expr[from_position] == '.') {
        number += expr[from_position];
        from_position++;
    }


    if (!number.empty())
        *ends_in = from_position;

    return number;
}

/**
 * Procura por uma token, seja numero ou operador em uma string
 * @param expr Expressão matemática
 * @param from_position Posição inicial de busca
 * @param ends_in Posição final de busca
 * @param is_number
 * @return
 */
string SearchForToken(string expr, int from_position, int *ends_in, bool *is_number) {
    // verifica se é uma token de fn
    string token = SearchForNonNumericToken(expr, from_position, ends_in);
    if (!token.empty())
        return token;

    // se não for uma fn, pode então ser uma token numérica
    string number = SearchForNumericToken(expr, from_position, ends_in);

    if (!number.empty())
        *is_number = true;

    return number;
}