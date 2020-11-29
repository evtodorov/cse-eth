#include <iostream>
#include <cmath>
#include <functional>
class MyFunc
{
    const double lambda;
public:
    typedef double returnType ;
    MyFunc(double l) : lambda(l) {};
    returnType operator() (double x)
    {
        return std::exp(-lambda * x);
    }
};

template<class T, class F>
inline double f_(T f, F dx, F x)
{
// f_ is an approximation of f around x
    return dx / 6 * (f(x) + 4 * f(x + dx / 2) + f(x + dx));

}

template<class T, class F>
typename F::returnType simpsons(F f, T a, T b, unsigned int N)
{
    T out = 0;
    T x = a;
    T dx = (b - a) / N;

    for (unsigned int i = 0; i < N; ++i)
    {
        // add each bin to the total
        out = out + f_(f, dx, a + i * dx);
    }

    return out;
}

int main()
{

    MyFunc f(3.5);
    std::negate<double> f2;
    double val = simpsons(f, 0., 1., 1000);

    std::cout << val;

    return 0;
}
