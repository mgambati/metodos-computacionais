#include <string>
#include <queue>
#include <iostream>
#include <map>
#include <stack>
#include "formula_parser.h"

using namespace std;

struct Operator {
    int precedence;
    bool left_associative;
};

map<char, Operator> op_info{
        {'+', {2, true}},
        {'-', {2, true}},
        {'/', {3, true}},
        {'*', {3, true}},
        {'^', {4, false}}
};

bool IsTokenOp(char token) {
    return op_info.find(token) != op_info.end();
}

int GetOpPrecedence(char token) {
    return op_info[token].precedence;
};

bool IsDigitOrDot(char c) {
    return isdigit(c) || c == '.';
}

bool OpHasHigherPrecedence(char first, char second) {
    return GetOpPrecedence(first) > GetOpPrecedence(second);
}

string FindNumberOrFuncInString(string expr, int from_position, int *ends_in) {

    // verifica se é uma função
    // sin, cos, log
    string fn3 = expr.substr(from_position, 3);
    if (fn3 == "sin" || fn3 == "cos" || fn3 == "log") {
        *ends_in = from_position + 3;
        return fn3;
    }

    string number = "";
    while (from_position < expr.length() && IsDigitOrDot(expr[from_position])) {
        number += expr[from_position];
        from_position++;
    }

    if (!number.empty())
        *ends_in = from_position;

    return number;
}

queue<string> ParseExpression(string expr) {
    queue<string> output_queue;
    stack<char> op_stack;

    int count = 0;
    while (count < expr.length()) {
        int ends_in_pos;
        string num_token = FindNumberOrFuncInString(expr, count, &ends_in_pos);
        char token = expr[count];

        // se for número, adicione a fila de saída
        if (!num_token.empty()) {
            output_queue.push(num_token);
            count = ends_in_pos;
        } else if (token == ')') {

            // mova todos os operadores da pilha até fila enquanto não aparecer um '('
            while (op_stack.top() != '(') {
                output_queue.push(string(1, op_stack.top()));
                op_stack.pop();
            }

            // descarte o ')'
            op_stack.pop();
            count++;
        } else {
            while (IsTokenOp(token) && !op_stack.empty() && OpHasHigherPrecedence(op_stack.top(), token)) {
                output_queue.push(string(1, op_stack.top()));
                op_stack.pop();
            }

            op_stack.push(token);
            count++;
        }
    }

    // esvazia a pilha de operadores e colocando-os na fila
    while (!op_stack.empty()) {
        output_queue.push(string(1, op_stack.top()));
        op_stack.pop();
    }

    return output_queue;
}

