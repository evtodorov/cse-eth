#include <iostream> //cout, endl
#include <cmath>    //abs
#include <vector>   //vector
#include <string>   //stod, stoi
#include <random>

const double pi = std::acos(-1);
typedef std::mt19937 randomN;
const double randMax = std::mt19937::max();
class Problem
{
///assuming symmetry in x and y
private:
    const double min_;
    const double max_;
    std::vector<double> end_points_;
    inline double g(double x, double y) const{
        ///inital conditions
        return x;
    }
public:
    Problem(double min, double max)
        : min_(min),
        max_(max)
    {    }


    randomN walk(double x0, double y0, double d, randomN rnd)
    {
        double xc = x0;
        double yc = y0;
        while(yc > min_ &&
              yc < max_ &&
              xc > min_ &&
              xc < max_)
        {
            double a = rnd()/randMax;

            double w = 2*pi*a;
            xc += d*std::cos(w);
            yc += d*std::sin(w);
        }
        end_points_.push_back(g(xc,yc));
        return rnd;
        //std::cout << xc << " " << yc << " " <<  g(xc,yc) << std::endl;
    }

    double expectation()
    {
        double sum = 0;
        for (auto p : end_points_){
            sum += p;
        }
        return sum/end_points_.size();
     //   return std::accumulate(end_points_.begin(),end_points_.end(),0) / end_points_.size();
    }
    double variance()
    {
        double N = end_points_.size();
        double avsq = 0;
        for (auto p : end_points_){
            avsq += p*p;
        }
        avsq /= N;
        double av = expectation();

        return N/(N-1) * (avsq - av*av);
    }

};

int main()
{
    const double min = -1.;
    const double max = 1.;
    const double d = 0.01;
    Problem diffusion (min,max);

    const int Nwalks = 10000;

    randomN rnd(548765);
    for (int i=0;i<Nwalks; ++i){
        rnd = diffusion.walk(0.3,0.4,0.01,rnd);
    }
    std::cout << diffusion.expectation() << "\n" << diffusion.variance();
    return 0;
}
