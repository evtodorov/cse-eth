// Mid-point approximation of the integral
// serial implementation
// author: etodorov

#include <iostream>
#include <cmath>
#include "timer.hpp"

using namespace std;

double riemannSum_serial(double a, double b, double (*f)(double x), int N){
    double dx = (b-a)/N;
    double S = 0;

    for(int i=1; i<=N; ++i){
            S += f(a+i*dx-dx/2.0)*dx;
    }

    return S;
}

double f ( double x){
    return sqrt(x)*log(x);
}

int main(){
// integrate sqrt(x)*ln(x) from 1 to 4 in 1000 steps
// serial implementation
    double a = 1.0;
    double b = 4.0;
    int N = 1000000;
    double output;
    cout << "Integrate sqrt(x)*ln(x) from " << a
         << " to " << b << " in " << N << " steps" << endl;

    timer t;
    t.start();
    output = riemannSum_serial(a,b,f,N);
    t.stop();
    cout.precision(16);
    cout << "Answer: " << output <<
                " in " << 1000*t.get_timing() << " ms. \n";

    return 0;
}
