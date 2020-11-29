/* Programming Techniques for Scientific Simulations, HS 2015
 * Exercise 6.2
 */

#include <cmath>
#include <iostream>

#include "simpson.hpp"

const double lambda=2.;

struct exp_minus_lambda_x {
  typedef double argument_type;
  typedef double result_type;

  exp_minus_lambda_x(const result_type lambda_value=1.0) : lambda_(lambda_value) {}

  inline result_type operator()(const argument_type x) const { return std::exp(-lambda_*x); }

  const result_type lambda_;
};

double exp_minus_lambda_x_func(const double x) { return std::exp(-lambda*x); }


int main() {
  const unsigned bins=128;
  const double a(0);
  const double b(1);

  std::cout.precision(15);
  // call using function object
  exp_minus_lambda_x func(lambda);
  std::cout << "int_a^b exp(-lambda*x) dx  = " << integrate<exp_minus_lambda_x>(a,b,bins,func) << "  (function object version)" << std::endl;

  // call using function pointer
  std::cout << "int_a^b exp(-lambda*x) dx  = " << integrate<double (*)(double)>(a,b,bins,exp_minus_lambda_x_func) << "  (function pointer version)" << std::endl;

  // analytic result for check
  std::cout << "            analytic result: " << (func(a)-func(b))/lambda << std::endl;

  return 0;
}
