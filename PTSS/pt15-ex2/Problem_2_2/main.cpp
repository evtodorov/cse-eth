#include "simpsons.hpp"
#include <iostream>
#include <cmath>
#include <functional>
int main(){
    double (*f)(double);

    f = plus;

    std::cout << simpsons(*f, M_PI, 0, 10);

    return 0;
}
