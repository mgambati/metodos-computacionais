#ifndef METODOS_COMP_INTERPOLATION_H
#define METODOS_COMP_INTERPOLATION_H
#include <vector>
using namespace std;

struct Point {
    double x, y;
};

void ShowInterpolationMenu();
void InterpolateLangrangeForFn(vector<Point> f);
vector<double> CalcLagrangeFactor(vector<Point> f, int i);
double CalcDenominator(vector<Point> f, int i);
void PrettyPrintPolynomial(vector<double> vector1);
vector<double> SumVectors(vector<double> vector1, vector<double> vector2);
vector<double> MultiplyPolynomials(vector<double> vector1, vector<double> vector2);
void InterpolateLagrange(vector<Point> f, double xi);
int FindInterval(vector<Point> f, double x);
void InterpolateLinearSpline(vector<Point> f, double x);

double A(vector<Point> f, int j);
double B(vector<Point> f, int j);
void InterpolateTrigonometric(vector<Point> f, double x);

#endif //METODOS_COMP_INTERPOLATION_H
