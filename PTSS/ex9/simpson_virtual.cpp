#include <iostream>
#include <cmath>
#include "simpson_virtual.hpp"
struct Concrete: Base {
    double operator() (double x) const
    {
        return x*std::sin(x);
    }
};

int main ()
{
    Concrete f;
    std::cout << integrate_virtual(0,1,100,f);

    return 0;
}
