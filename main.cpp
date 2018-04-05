#include <iostream>
#include <stack>
#include "formula_parser.h"

using namespace std;

int main() {
    cout << "Digite uma fórmula:" << endl;
    string formula;

    cin >> formula;

    stack<string> rpn_expr = ParseExpressionToRPN(formula);

    cout << "Valor de x:" << endl;

    double x;
    cin >> x;

    double result = SolveRPNExpression(rpn_expr, x);
    cout << result << endl;
    return 0;
}