#include <iostream> //cout, endl
#include <cmath>    //abs
#include <vector>   //vector
#include <string>   //stod, stoi
#include <random>
#include <omp.h>
#include "timer.hpp"
const double pi = std::acos(-1);
typedef std::mt19937 randomN;
const double randMax = std::mt19937::max();
class Problem
{
///assuming symmetry in x and y
private:
    const double min_;
    const double max_;
    double sum_ = 0;
    double sumSq_ = 0;
    unsigned int count_ = 0;
    inline double g(double x, double y) const
    {
        ///inital conditions
        if (x < min_){
            x = min_;
        }
        else if(x > max_){
            x = max_;
        }
        return x;
    }
public:
    Problem(double min, double max)
        : min_(min),
          max_(max)
    {    }


    void walk(double x0, double y0, double d, randomN& rnd)
    {
        double xc = x0;
        double yc = y0;

        while(  yc > min_ &&
                yc < max_ &&
                xc > min_ &&
                xc < max_)
        {
            double a = rnd() / randMax;

            double w = 2 * pi * a;
            xc += d * std::cos(w);
            yc += d * std::sin(w);
        }

        double rho = g(xc, yc);
        //TODO: no need to sync, no one cares when I add it
        #pragma omp atomic
            sum_+=rho;
        #pragma omp atomic
            sumSq_+= rho*rho;
        #pragma omp atomic
            ++count_;

    }

    void solve(double x0, double y0, double d, int Nwalks, int Nthreads)
    {
        #pragma omp parallel
        {
            randomN rnd(omp_get_thread_num() * 2164831);
            #pragma omp for
            for (int i = 0; i < Nwalks; ++i)
            {
                walk(x0, y0, d, rnd);
            }
        }


    }
    double expectation()
    {
       return sum_/count_;
    }
    double variance()
    {
        double av = expectation();
        double N = count_;

        return std::sqrt( (sumSq_ - av * av / N) / (N*(N-1)));
    }

};

int main(int argc, char** argv)
{
    const double min = -1.;
    const double max = 1.;
    const double d = 0.01;
    const double x0 = 0.3;
    const double y0 = 0.4;
    Problem diffusion (min, max);

    const int Nwalks = std::stoi(argv[2]);
    const int Nthreads = std::stoi(argv[1]);
    omp_set_num_threads(Nthreads);
    timer t;
for (int i=1; i<18; ++i){
    t.start();
    diffusion.solve(x0, y0, d, std::pow(2,i), Nthreads);
    t.stop();
    std::cout << "2^" << i << "\t" << diffusion.expectation() << "+-" << diffusion.variance() << "\t" << t.get_timing() << " s\n";
}


    //std::cout << omp_get_max_threads() << "\t" << Nwalks << "\t" << t.get_timing() <<std::endl;


    return 0;
}
