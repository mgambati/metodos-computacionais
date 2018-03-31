#include <iostream>
#include <stack>
#include "formula_parser.h"

using namespace std;

int main() {
    cout << "Digite uma fórmula:" << endl;
    string formula;

    cin >> formula;

    stack<string> result = ParseExpressionToRPN(formula);

    while (!result.empty()) {
        cout << result.top() + " ";
        result.pop();
    }

    return 0;
}