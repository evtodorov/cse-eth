#include <iostream>
#include <cmath>
#include <string>
#include "timer.hpp"

#include "simpson_template.hpp"
#include "simpson_virtual.hpp"

using std::cout; using std::endl; using std::stoi;


inline double f6 (double x){return 1;}

struct F6_template
{
    typedef double argument_type;
    typedef double result_type;

    F6_template() {}
    inline result_type operator()(const argument_type x) const { return f6(x); }
};

struct F6_virtual : Base
{
    double operator() (double x) const
    {
        return f6(x);
    }
};
double integrate_hardcoded(double a, double b, unsigned N)
{
        double out = 0;
    double x = a;
    double dx = (b - a) / N;

    for (unsigned i = 0; i < N; ++i)
    {
        double temp = f6(x);
        x += dx / 2;
        temp += 4*f6(x);
        x += dx / 2;
        temp += f6(x);
        out +=  dx / 6 * temp;
    }

    return out;
}

double integrate_pointer (double a, double b, unsigned N, double (*f) (double) )
{
    double out = 0;
    double half_dx = (b - a) / 2.0 / N;
    double temp = 0;
    double mid = f(a);
    for (unsigned i = 0; i < N; ++i)
    {
        a += half_dx;
        temp = mid + 4*f(a);
        a += half_dx;
        mid = f(a);
        out +=  half_dx / 3 * (temp + mid);
    }

    return out;
}
struct exp_minus_lambda_x {
  typedef double argument_type;
  typedef double result_type;

  exp_minus_lambda_x(const result_type lambda_value=1.0) : lambda_(lambda_value) {}

  inline result_type operator()(const argument_type x) const { return std::exp(-lambda_*x); }

  const result_type lambda_;
};
const double lambda=2.;
double exp_minus_lambda_x_func(const double x) { return std::exp(-lambda*x); }


int main (int argc, char** argv)
{

    const unsigned long itterations = argc > 1 ? stoi(argv[1]) : 1e+3;
    const unsigned bins = argc > 2 ? stoi(argv[2]) : 1e+3;
    const double a = 0;
    const double b = 100;

    double out;

    Timer t;
    t.start();
    for(unsigned long i=0; i < itterations; ++i){
        out = integrate_hardcoded(a,b,bins);
    }

    t.stop();
    cout << "hardcoded\t" << out << "\t" << t.duration() << endl;


    t.start();
    for(unsigned long i=0; i < itterations; ++i)
        out = integrate_pointer(a,b,bins,f6);
    t.stop();
    cout << "pointer\t\t" << out << "\t" << t.duration() << endl;


    exp_minus_lambda_x func(lambda);
    integrate_template<exp_minus_lambda_x>(a,b,bins,func);

    F6_template f6_template;
    t.start();
    for(unsigned long i=0; i < itterations; ++i){
        out = integrate_template<F6_template>(a,b,bins,f6_template);
    }
    t.stop();
    cout << "template\t" <<out << "\t" << t.duration() << endl;

    F6_virtual f6_virtual;
    t.start();
    for(unsigned long i=0; i < itterations; ++i){
        out = integrate_virtual(a,b,bins,f6_virtual);
    }
    t.stop();
    cout << "virtual\t\t" << out << "\t" << t.duration() << endl;


    return 0;
}
