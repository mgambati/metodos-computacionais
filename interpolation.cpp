#include <iostream>
#include <vector>
#include <cmath>
#include "termcolor.hpp"
#include "interpolation.h"

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
            InterpolateLagrange(points, xi);
            break;
        case 2:
            cout << "Qual ponto Xi deseja calcular?" << endl;
            cin >> xi;
            InterpolateLinearSpline(points, xi);
            break;
        case 3:
            cout << "Qual angular \u03B8(x) deseja calcular? (entrada multiplicada por PI automaticamente)" << endl;
            cin >> xi;
            InterpolateTrigonometric(points, xi);
            break;
    }

}


void InterpolateLagrange(vector<Point> f, double xi) {
    double result = 0;

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
    cout << "A" << j << ": " << result << endl;
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
    cout << "B" << j << ": " << result << endl;

    return result;
}


void InterpolateTrigonometric(vector<Point> f, double x) {
    double result = A(f, 0) / 2;
    int m;

    if (f.size() % 2) { // odd
        m = (int) (f.size() - 1) / 2;
        for (int k = 1; k <= m; ++k) {
            result += A(f, k) * cos(k * x) + B(f, k) * sin(k * x);
        }

    } else {
        m = (int) f.size() / 2;
        for (int k = 1; k < m; ++k) {
            result += A(f, k) * cos(k * x) + B(f, k) * sin(k * x);
        }

        result += (A(f, m) / 2) * cos(m * x);
    }

    cout << "Resultado: f(" << x << ") = " << result << endl;
}