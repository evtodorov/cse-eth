#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

const std::complex<double> I (0,1);

struct Particle
{
    std::complex<double> z;
    std::complex<double> v;
    double gamma;
    double h;

    Particle (double x0, double y0, int N)
    : z(x0 + I*y0),
      h( 1.0/N),
      gamma(-4*x0/std::sqrt(1-4*x0*x0)*h)
    {}

};

int main (int argc, char** argv)
{
    const int N = 10000;

    const double L  = 1;
    const double y0 = 0;
    const double x0 = -.5;

    const double dt = 1e-3;

    std::vector<std::complex<double>> particles;

    for (int j=0; j<N; ++j){
        Particle particle(x0+(j-x0)/N,y0,N);
        particles.push_back(particle);
    }

    std::cout << particles[256].gamma;

    return 0;
}
