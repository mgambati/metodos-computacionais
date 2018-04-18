//
// Created by mgambati on 17/04/18.
//

#ifndef METODOS_COMP_CMAKE_ZERO_OF_FUNCTION_H
#define METODOS_COMP_CMAKE_ZERO_OF_FUNCTION_H

double f(double x);

double fdx(double x);

void ShowZeroMenu();
void ReadInputForAB(int method);
void ReadInputForNewton();

double CalculateBissection(double a, double b, int it_count);
double CalculateFalsePosition(double a, double b, int it_count);
double CalculateNewton(double x, int it_count);
double CalculateSecant(double x, double y, int it_count);

#endif //METODOS_COMP_CMAKE_ZERO_OF_FUNCTION_H
