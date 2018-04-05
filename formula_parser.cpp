#include <string>
#include <map>
#include <stack>
#include <cmath>
#include "formula_parser.h"
#include "token_helper.h"

using namespace std;

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

            // Evita que caso os parenteses sejam de uma função, ela seja deixada na pilha
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
                        !op_stack.empty() && (CompareOpPrecedenceOrLA(op_stack.top(), token)
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

/**
 * Calcula valores de funções unárias
 * @param op
 * @param x
 * @return
 */
double SolveUnaryOperation(string op, double x) {
    if (op == "sin")
        return sin(x);
    if (op == "cos")
        return cos(x);
    if (op == "tg")
        return tan(x);
    if (op == "log")
        return log10(x);

    return log(x); // ln
}

/**
 * Calcula o valor de uma operação com operador binário
 * @param op
 * @param x
 * @param y
 * @return
 */
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

/**
 * Resolve uma Reverse Polish Notation
 * @param expr_stack
 * @param x_value
 * @return
 */
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


