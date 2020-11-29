#include "simpsons.hpp"
#include <iostream>
#include <cmath>

int main(){
    double (*f)(double);

    f = sin;

    std::cout << simpsons(*f, M_PI, 0, 10);

    return 0;
}
