#include <iostream>

double func (double& x){
    double y = x;
    ++x;
    return y;
}

int main ()
{
    double x = 5;

    double y = func(x);
    std::cout << y << x;

    return 0;
}
