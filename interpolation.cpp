#include <iostream>
#include <vector>
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
    cout << "Qual ponto Xi deseja calcular?" << endl;
    cin >> xi;

    switch (selected) {
        case 1:
            InterpolateLagrange(points, xi);
            break;
        case 2:
            InterpolateLinearSpline(points, xi);
            break;
    }

}


void InterpolateLagrange(vector<Point> f, int xi) {
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

    double result = x0.y * (x - x1.x) / (x0.x - x1.x) + x1.y * (x - x0.x)/ (x1.x - x0.x);

    cout << "Usando o intervalo: [" << x0.x << ", " << x1.x << "]" << endl;
    cout << "Resultado: f(" << x << ") = " << result << endl;
}
