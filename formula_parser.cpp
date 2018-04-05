#include <string>
#include <map>
#include <stack>
#include <cmath>
#include "formula_parser.h"

using namespace std;

struct TokenInfo {
    int precedence;
    bool left_associative;
};

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
            "(", ")", "cos", "sin", "tg", "log", "ln"
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

int GetLeftAssociativity(string token) {
    return op_info[token].left_associative;
};

double GetConstValue(string token) {
    if (token == "pi")
        return M_PI;
    else if (token == "e")
        return M_E;
}

/**
 * Retorn true se o first tiver precedencia maior ou é associativo a direita
 * @param first
 * @param second
 * @return
 */
bool CompOPPrecedencOrLA(string first, string second) {
    int p_first = GetOpPrecedence(first);
    int p_second = GetOpPrecedence(second);
    bool has_eq_p = p_first == p_second;

    if (has_eq_p)
        return GetLeftAssociativity(first);

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
    while (fn_token_size <= 3) {
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

/**
 * Transforma uma expressão matemática em uma Reverse Polish Notation
 * usando o algoritmo Shunting Yard.
 *
 * Operadores implementados: +, -, /, *, ^
 * Funcões implementadas: sin, cos, ln, tg, log
 * @param expr
 * @return
 */
stack<string> ParseExpressionToRPN(string expr) {
    stack<string> output_stack;
    stack<string> op_stack;

    int count = 0;
    while (count < expr.length()) {

        int token_ends_in_pos;
        bool token_is_number = false;
        string token = SearchForToken(expr, count, &token_ends_in_pos, &token_is_number);

        // se for número, adicione a fila de saída
        if (token_is_number || IsTokenConst(token)) {
            output_stack.push(token);
            count = token_ends_in_pos;
        } else if (token == ")") {
            // mova todos os operadores da pilha até fila enquanto não aparecer um '('
            while (op_stack.top() != "(") {
                output_stack.push(op_stack.top());
                op_stack.pop();
            }

            // descarte o ')'
            op_stack.pop();
            count = token_ends_in_pos;

            if (IsTokenFn(op_stack.top())) {
                output_stack.push(op_stack.top());
                op_stack.pop();
            }
        } else if (IsTokenFn(token)) {
            op_stack.push(token);
            count = token_ends_in_pos;

        } else {
            if (!op_stack.empty() && op_stack.top() != "(") {
                while (
                        !op_stack.empty() && (CompOPPrecedencOrLA(op_stack.top(), token)
                                              || IsTokenFn(token))
                        ) {
                    output_stack.push(op_stack.top());
                    op_stack.pop();
                }
            }

            op_stack.push(token);
            count = token_ends_in_pos;
        }
    }


    // esvazia a pilha de operadores e colocando-os na fila
    while (!op_stack.empty()) {
        output_stack.push(op_stack.top());
        op_stack.pop();
    }

    stack<string> reversed_output;
    while (!output_stack.empty()) {
        reversed_output.push(output_stack.top());
        output_stack.pop();
    }

    return reversed_output;
}

double SolveUnaryOperation(string op, double x) {
    if (op == "sin")
        return sin(x);
    else if (op == "cos")
        return cos(x);
    else if (op == "tg")
        return tan(x);
    else if (op == "log")
        return log10(x);


    return log(x); // ln
}

double SolveBinaryOperation(string op, double x, double y) {
    if (op == "+")
        return x + y;
    if (op == "-")
        return x - y;
    if (op == "*")
        return x * y;
    if (op == "/")
        return x / y;

    return pow(x, y);
}

double SolveRPNExpression(stack<string> expr_stack, double x_value) {
    stack<double> aux_stack;

    while (!expr_stack.empty()) {
        string token = expr_stack.top();

        // operadores binarios
        if (IsTokenOp(token)) {
            double y = aux_stack.top();
            aux_stack.pop();

            double x = aux_stack.top();
            aux_stack.pop();

            aux_stack.push(SolveBinaryOperation(token, x, y));
            expr_stack.pop();
        }

            // Operadores unários
        else if (IsTokenFn(expr_stack.top())) {
            double x = aux_stack.top();
            aux_stack.pop();

            aux_stack.push(SolveUnaryOperation(token, x));
            expr_stack.pop();
        }

            // Tokens numéricas são convertidas para double.
        else {
            double x;
            if (token == "x") {
                x = x_value;
            } else if (IsTokenConst(token)) {
                x = GetConstValue(token);
            } else {
                x = stod(token);
            }
            expr_stack.pop();

            aux_stack.push(x);
        }

    }

    return aux_stack.top();
}


