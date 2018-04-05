#include <iostream>
#include <stack>
#include "formula_parser.h"

using namespace std;

int main() {
    cout << "Digite uma fórmula:" << endl;
    string formula;

    cin >> formula;

    stack<string> rpn_expr = ParseExpressionToRPN(formula);
    double result = SolveRPNExpression(rpn_expr, 0);

    cout << result << endl;
    return 0;
}