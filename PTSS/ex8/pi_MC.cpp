#include <iostream>
#include <random>
#include <cmath>

using std::cout; using std::endl;

const double PI = std::acos(-1);


int main()
{
    std::mt19937 rnd1(3423);
    double hits = 1e+8;
    long int trials = 0;
    for(long int i = 0; i < hits; ++i)
    {
        double x, y;
        do{
            ++trials;
            x = std::generate_canonical<double,15>(rnd1);
            y = std::generate_canonical<double,15>(rnd1);
        }
        while(x*x+y*y > 1);
    }
    cout.precision(15);
    cout << " " << PI << endl << "-" << endl << " " << 4*hits/trials << endl << PI - 4*hits/trials << endl;


    return 0;
}
