/* Programming Techniques for Scientific Simulations, HS 2015
 * Week 12
 */

#include <iostream>
#include "algorithmic_derivation.hpp"

// expression: 5*x*(x+1)+72*x+38 = 5*x^2 + 77*x + 38
// derivative: 10*x+77

int expr(const int _x)
{
  Variable<int> x;
  return (constant(5)*x*(x+constant(1))+constant(72)*x+constant(38))(_x);
}

int expr_deriv(const int _x)
{
  Variable<int> x;
  return (constant(5)*x*(x+constant(1))+constant(72)*x+constant(38)).derivative(_x);
}

int main()
{
  Variable<int> x;
  std::cout << expr(8)  << ' ' << expr_deriv(8)
            << std::endl;
  //std::cout << (constant(4)*x*x).derivative()(42)
  //          << std::endl;

  return 0;
}
