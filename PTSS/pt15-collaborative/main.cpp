#include <iostream> //cout
#include <cmath>    //sin
#include "simpson_integral.hpp"

double f(double x){
    return std::sin(x);
}

int main(){

    double a = 0;   //interval start
    double b = 1;   //interval end
    int bins = 100; //number of intervals
    double S;

    S = simpson_integral(f,a,b,bins);

    std::cout << S;

    return 0;
}
