#ifndef METODOS_COMP_INTERPOLATION_H
#define METODOS_COMP_INTERPOLATION_H
#include <vector>
using namespace std;

struct Point {
    double x, y;
};

void ShowInterpolationMenu();
void InterpolateLagrange(vector<Point> f, int xi);
int FindInterval(vector<Point> f, double x);
void InterpolateLinearSpline(vector<Point> f, double x);
#endif //METODOS_COMP_INTERPOLATION_H
