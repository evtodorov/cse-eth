#include <cassert>
#include <limits>
#include <cstddef>
#include "simpsons.hpp"


double f_(double (*f)(double x), double dx, double x){
// f_ is an approximation of f around x
    return dx/6*(f(x)+ 4*f(x+dx/2)+ f(x+dx));

}

double simpsons(double (*f)(double x), double b, double a, int N){
    //check input
    assert(b > a);
    assert(N > 0);
    assert(f != NULL);

    //compute dx (delta x)
    double dx = (b-a)/N;

    assert (dx > std::numeric_limits<double>::epsilon());

    double out = 0;
    //for every bin
    for (int i=0; i < N; i++){
        // add each bin to the total
        out += f_(*f,dx,a+i*dx);
    }

    return out;
}
