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

bool GetOpLeftAssociativity(char token) {
    return op_info[token].left_associative;
};

bool IsDigitOrDot(char c) {
    return isdigit(c) || c == '.';
}


string FindNumberInString(string expr, int from_position, int *ends_in) {
    string number;

    while (from_position < expr.length() && IsDigitOrDot(expr[from_position])) {
        if (!IsDigitOrDot(expr[from_position]))
            break;
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

    int i = 0;
    while (i < expr.length()) {
        int num_token_ends_in;
        string num_token = FindNumberInString(expr, i, &num_token_ends_in); // Find Está pulando tokens
        char token = expr[i];

        if (!num_token.empty()) {
            output_queue.push(num_token);
            i = num_token_ends_in;
        } else if (token == ')') {

            while (op_stack.top() != '(') {
                output_queue.push(string(1, op_stack.top()));
                op_stack.pop();
            }

            op_stack.pop();
            i++;
        } else {
            while (IsTokenOp(token) && GetOpPrecedence(op_stack.top()) > GetOpPrecedence(token)) {
                output_queue.push(string(1, op_stack.top()));
                op_stack.pop();
            }

            op_stack.push(token);
            i++;
        }
    }

    while (!op_stack.empty()) {
        output_queue.push(string(1, op_stack.top()));
        op_stack.pop();
    }

    cout << "Parsed." << endl;

    return output_queue;
}