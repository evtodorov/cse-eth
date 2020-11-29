#ifndef SIMPSONS_HPP_INCLUDED
#define SIMPSONS_HPP_INCLUDED

double simpsons(double (*f)(double), double, double, int);
/*
double simpsons(double (*f)(double x), double b, double a, int N)

Calculates the numerical integral of f, using Simpson's rule

b > a
N < (b-a)/numeric_limits<double>::epsilon()

f must be a function of one variable
*/
#endif // SIMPSONS_HPP_INCLUDED
