#include <iostream>
#include <queue>
#include "formula_parser.h"

using namespace std;

int main() {
    cout << "Digite uma fórmula:" << endl;
    string formula;

    cin >> formula;

    queue<string> result = ParseExpression(formula);

    while (!result.empty()) {
        cout << result.front();
        result.pop();
    }

    return 0;
}