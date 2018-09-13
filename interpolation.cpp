#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <stack>
#include "termcolor.hpp"
#include "interpolation.h"
#include "formula_parser.h"

using namespace std;

void ShowInterpolationMenu() {
    cout << termcolor::bold << termcolor::blue << "--------------- Métodos para interpolação ---------------"
         << endl << termcolor::reset;
    cout << "Qual método deseja usar para calcular?" << endl;
    cout << "1 - Lagrange || 2 - Spline linear || 3 - Inter. Trigonométrica || 4 - Newton" << endl;

    int selected, n;
    cin >> selected;

    vector<Point> points;
    cout << "Quantos pontos deseja inserir?" << endl;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Point point;
        cout << "------------ Ponto " << i + 1 << " ------------" << endl;
        cout << "x: " << endl;
        cin >> point.x;
        cout << "y: " << endl;
        cin >> point.y;
        points.push_back(point);
    }

    double xi;

    switch (selected) {
        case 1:
            cout << "Qual ponto Xi deseja calcular?" << endl;
            cin >> xi;
            InterpolateLangrangeForFn(points);
            InterpolateLagrange(points, xi);
            break;
        case 2:
            cout << "Qual ponto Xi deseja calcular?" << endl;
            cin >> xi;
            InterpolateLinearSplineForFn(points);
            InterpolateLinearSpline(points, xi);
            break;
        case 3:
            cout << "Qual angular \u03B8(x) deseja calcular? (entrada multiplicada por PI automaticamente)" << endl;
            cin >> xi;
            InterpolateTrigonometric(points, xi);
            break;
        case 4:
            InterpolateNewtonForFn(points);
            break;
    }

}

vector<double> MultiplyPolynomials(vector<double> vector1, vector<double> vector2) {
    vector<double> vector3(vector1.size() + vector2.size());

    for (int i = 0; i < vector1.size(); ++i) {
        for (int j = 0; j < vector2.size(); ++j) {
            vector3[i + j] = vector3[i + j] + vector1[i] + vector2[j];
        }
    }
    return vector3;
}

vector<double> SumVectors(vector<double> vector1, vector<double> vector2) {
    vector<double> vector3(vector1.size());

    for (int i = 0; i < vector1.size(); ++i) {
        vector3[i] = vector1[i] + vector2[i];
    }

    return vector3;
}

void PrettyPrintPolynomial(vector<double> vector1) {
    cout << termcolor::magenta << "f(x) = ";
    for (int i = vector1.size() - 1; i > 0; --i) {
        if (vector1[i] != 0.0) {
            cout << vector1[i] << "*x^" << i;
            if (i != 1)
                cout << " + ";
        }
    }

    cout << " + " << vector1[0] << endl << termcolor::reset;
}


double CalcDenominator(vector<Point> f, int i) {
    double multipliyer = 1.0;
    for (int j = 0; j < f.size(); ++j) {
        if (j == i)
            continue;
        multipliyer = multipliyer * (f[i].x - f[j].x);
    }
    return multipliyer;
}

vector<double> CalcLagrangeFactor(vector<Point> f, int i) {
    vector<double> vector1(2);
    vector<double> vector2(f.size());
    vector2[0] = 1.0;
    double d = CalcDenominator(f, i);

    for (int j = 0; j < f.size(); ++j) {
        if (j == i)
            continue;
        vector1[0] = -1 * f[j].x;
        vector1[1] = 1;

        vector2 = MultiplyPolynomials(vector1, vector2);
    }

    for (int k = 0; k < f.size(); ++k) {
        vector2[k] = vector2[k] / d;
    }
    return vector2;
}

void InterpolateLangrangeForFn(vector<Point> f) {
    vector<double> partialPoly(f.size());
    vector<double> finalPoly(f.size());

    for (int i = 0; i < f.size(); ++i) {
        partialPoly = CalcLagrangeFactor(f, i);

        for (int j = 0; j < partialPoly.size(); ++j) {
            partialPoly[j] = partialPoly[j] * f[i].y;
        }
        finalPoly = SumVectors(finalPoly, partialPoly);
    }

    PrettyPrintPolynomial(finalPoly);
}

void InterpolateLagrange(vector<Point> f, double xi) {
    double result = 0;
    string resultStr;

    for (int i = 0; i < f.size(); i++) {
        double term = f[i].y;

        for (int j = 0; j < f.size(); j++) {
            if (j != i) {
                term = term * (xi - f[j].x) / (f[i].x - f[j].x);
            }
        }

        result += term;
    }

    cout << "Resultado: f(" << xi << ") = " << result << endl;
}

int FindInterval(vector<Point> f, double x) {
    int lowIndex = 0;

    for (int i = 0; i < f.size(); i++) {
        // find lower nearest point index
        if (f[i].x < x && f[i].x > f[lowIndex].x) {
            lowIndex = i;
        }
    }

    return lowIndex;
}

void InterpolateLinearSplineForFn(vector<Point> f) {
    for (int i = 1; i < f.size(); ++i) {
        cout <<termcolor::magenta << "S" << i << " = (";
        double denominator = f[i].x - f[i - 1].x;

        cout << (-1 * f[i - 1].y + f[i].y) / denominator << ")*x + (" <<
                     ((f[i - 1].y * f[i].x) - (f[i].y * f[i - 1].x)) / denominator << ")";

        cout << termcolor::reset << endl;
    }
}

void InterpolateLinearSpline(vector<Point> f, double x) {
    int x0Index;
    x0Index = FindInterval(f, x);

    Point x0 = f[x0Index], x1 = f[x0Index + 1];

    double result = x0.y * (x - x1.x) / (x0.x - x1.x) + x1.y * (x - x0.x) / (x1.x - x0.x);

    cout << "Usando o intervalo: [" << x0.x << ", " << x1.x << "]" << endl;
    cout << "Resultado: f(" << x << ") = " << result << endl;
}

/**
 * Calcula X[k] para pontos equidistantes
 * @param k
 * @param N
 * @return
 */
double Xk(int k, int N) {
    return k * 2 * M_PI / N;
}

/**
 * Calcula A[j], usado para interpolação trigonometrica
 * @param f
 * @param j
 * @return
 */
double A(vector<Point> f, int j) {
    double result = 0;
    for (int k = 0; k < f.size(); k++) {
        result += f[k].y * cos(j * Xk(k, (int) f.size()));
    }
    result = (2.0 / f.size()) * result;
    return result;
}

/**
 * Calcula B[j], usado para interpolação trigonometrica
 * @param f
 * @param j
 * @return
 */
double B(vector<Point> f, int j) {
    double result = 0;
    for (int k = 0; k < f.size(); k++) {
        result += f[k].y * sin(j * Xk(k, (int) f.size()));
    }
    result = (2.0 / f.size()) * result;

    return result;
}


void InterpolateTrigonometric(vector<Point> f, double x) {
    double result = A(f, 0) / 2;
    stringstream resultStream;
    int m;

    if (f.size() % 2) { // odd
        m = (int) (f.size() - 1) / 2;
        for (int k = 1; k <= m; ++k) {
            result += A(f, k) * cos(k * x) + B(f, k) * sin(k * x);
            resultStream << A(f, k) << "*cos(" << k << "*x)+" << B(f, k) << "*sin(" << k << "*x)";
        }

    } else {
        m = (int) f.size() / 2;
        for (int k = 1; k < m; ++k) {
            result += A(f, k) * cos(k * x) + B(f, k) * sin(k * x);
            resultStream << A(f, k) << "*cos(" << k << "*x)+" << B(f, k) << "*sin(" << k << "*x)";
        }

        result += (A(f, m) / 2) * cos(m * x);
        resultStream << A(f, m) / 2 << "*cos(" << m << "*x)";
    }

    cout << termcolor::magenta << "Resultado: f(x) = " << resultStream.str() << termcolor::reset << endl;
    cout << "Resultado: f(" << x << ") = " << result << endl;
}

void InterpolateNewtonForFn(vector<Point> f) {
    int max= 50;
    double matrix1[max][max];
    double matrix2[max][max];


    // init matrix
    for (int i = 0; i < (max - 1); i++) {
        for (int j = 0; j < (max - 1); j++) {
            matrix1[i][j] = -999;
            matrix2[i][j] = -999;
        }
    }

    // build matrix
    for (int i = 0; i < f.size(); i++) {
       matrix1[0][i] = f[i].x;
       matrix1[1][i] = f[i].y;
    }

    for (int i = 0; i < f.size(); i++)
        matrix2[i][0] = matrix1[1][i];

    int line = (int) f.size(), aux = 0;
    for (int ord = 1; ord < f.size(); ord++) {
        line--;
        aux = ord;
        for (int j = 0; j < line; j++) {
            matrix2[j][ord] = (matrix2[j + 1][ord - 1] - matrix2[j][ord - 1]) / (matrix1[0][aux] - matrix1[0][j]);
            aux++;
        }
    }

    string auxStr = "";
    for (int ord = 0; ord < f.size() - 1; ord++) {
        stringstream auxStrStream;
        for (int i = 0; i < ord + 1; i++) {
            if (matrix1[0][i] >= 0)
                auxStrStream << "(x - " << matrix1[0][i] << ")";
            else
                auxStrStream << "(x + " << matrix1[0][i] * -1 << ")";
        }
        auxStrStream << "(" << matrix2[0][ord + 1] << ")";
        auxStr += auxStrStream.str();
        if (ord < f.size() - 2)
            auxStr = auxStr + " + ";
    }
    cout << termcolor::magenta << "p(x) = " << matrix2[0][0] << " + " << auxStr << termcolor::reset << endl;
}
