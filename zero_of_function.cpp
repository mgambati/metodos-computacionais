#include <iostream>
#include <stack>
#include <cmath>
#include "zero_of_function.h"
#include "formula_parser.h"
#include "termcolor.hpp"

using namespace std;


double epsilon;
string formula, derivative;
stack<string> parsed_formula, parsed_derivative;

double CalculateBissection(double a, double b, int it_count) {
    if (it_count > 10000) {
        cout << termcolor::red << "Iterações esgotadas, a função não converge." << endl;
        return NAN;
    }
    double fa = f(a), fb = f(b), fx, x;

    x = (a * fb - b * fa) / (fb - fa);
    fx = f(x);

    if (abs(fx) <= epsilon) {
        cout << termcolor::magenta << "Total de iterações: " << it_count << endl;
        return x;
    }

    if (fx < 0)
        return CalculateBissection(x, b, ++it_count);

    return CalculateBissection(a, x, ++it_count); // fx > 0
}

double CalculateFalsePosition(double a, double b, int it_count) {
    if (it_count > 10000) {
        cout << termcolor::red << "Iterações esgotadas, a função não converge." << endl;
        return NAN;
    }

    double fa = f(a), fb = f(b), fx, x;

    x = ((a * fb - fa * b) / (fb - fa));
    fx = f(x);

    if (abs(fx) <= epsilon) {
        cout << termcolor::magenta << "Total de iterações: " << it_count << endl;

        return x;
    }
    if (fa * fx < 0)
        return CalculateFalsePosition(a, x, ++it_count);
    return CalculateFalsePosition(x, b, ++it_count);
}

double CalculateNewton(double x, int it_count) {
    if (it_count > 10000) {
        cout << termcolor::red << "Iterações esgotadas, a função não converge." << endl;
        return NAN;
    }

    double fx = f(x), rdx;
    if (abs(fx) <= epsilon) {
        cout << termcolor::magenta << "Total de iterações: " << it_count << endl;
        return x;
    }
    rdx = fdx(x);
    return CalculateNewton(x - (fx / rdx), ++it_count);
}

double CalculateSecant(double a, double b, int it_count) {
    if (it_count > 10000) {
        cout << termcolor::red << "Iterações esgotadas, a função não converge." << endl;
        return NAN;
    }

    double fa = f(a), fb = f(b), x, fx;

    x = b - (b - a) * fb / (fb - fa);
    fx = f(x);
    if (abs(fx) < epsilon) {
        cout << termcolor::magenta << "Total de iterações: " << it_count << endl;
        return x;
    }

    return CalculateSecant(b, x, ++it_count);
}


// helpers

double f(double x) {
    return SolveRPNExpression(parsed_formula, x);
}

double fdx(double x) {
    return SolveRPNExpression(parsed_derivative, x);
}

/**
 * Printa um menu bonitinho
 */
void ShowZeroMenu() {
    cout << termcolor::bold << termcolor::blue << "--------------- Métodos para encontrar 0 de funções ---------------"
         << endl << termcolor::reset;
    cout << "Qual método deseja usar para calcular?" << endl;
    cout << "1 - Bissecção || 2 - Posição Falsa || 3 - Newton || 4 - Secante" << endl;

    int selected;
    cin >> selected;

    cout << "Insira uma fórmula para computar (ex: cos(3*pi/2)+x^2)" << endl;
    cout << "Funções válidas: sin, cos, log (base 10), ln, tg" << endl;
    cout << "Operadores válidos: +, -, /, *, ^" << endl;

    cin >> formula;
    parsed_formula = ParseExpressionToRPN(formula);

    cout << "Qual o erro mínimo?" << endl;

    cin >> epsilon;

    switch (selected) {
        case 1: {
            cout << termcolor::bold << termcolor::blue << "--------------- Método da Bissecção ---------------" << endl
                 << termcolor::reset;
            ReadInputForAB(selected);
            break;
        }
        case 2: {
            cout << termcolor::bold << termcolor::blue << "--------------- Método da Posição Falsa --------------- "
                 << endl << termcolor::reset;
            ReadInputForAB(selected);
            break;
        }
        case 3: {
            cout << termcolor::bold << termcolor::blue << "--------------- Método Newton ---------------" << endl
                 << termcolor::reset;
            ReadInputForNewton();
            break;
        }
        case 4: {
            cout << termcolor::bold << termcolor::blue << "--------------- Método da Secante ---------------" << endl
                 << termcolor::reset;
            ReadInputForAB(selected);
            break;
        }
        default:
            cout << termcolor::red << "Nenhum método válido selecionado." << endl;
    }
}

void ReadInputForAB(int method) {
    double a, b;
    cout << "Valor de a: " << endl;
    cin >> a;

    cout << "Valor de b: " << endl;
    cin >> b;

    cout << termcolor::bold << termcolor::blue << "--------------- Resultados ---------------" << endl
         << termcolor::reset;

    double result = NAN;

    if (method == 1) result = CalculateBissection(a, b, 0);
    if (method == 2) result = CalculateFalsePosition(a, b, 0);
    if (method == 4) result = CalculateSecant(a, b, 0);

    if (!isnan(result)) {
        cout << termcolor::green << "O zero está em x = " << result << endl;
    }
}

void ReadInputForNewton() {
    cout << "Insira a derivada f(x):" << endl;
    cin >> derivative;
    parsed_derivative = ParseExpressionToRPN(derivative);

    double x;
    cout << "Valor de x: " << endl;
    cin >> x;

    cout << termcolor::bold << termcolor::blue << "--------------- Resultados ---------------" << endl
         << termcolor::reset;

    double result = CalculateNewton(x, 0);

    if (!isnan(result)) {
        cout << termcolor::green << "O zero está em x = " << result << endl;
    }
}