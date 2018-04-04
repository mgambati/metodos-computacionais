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
//    cout << cos(1* M_PI/2) <<endl;
    return 0;
}