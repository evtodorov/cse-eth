#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <complex>
#include <string>
#include <vector>
#include <cmath>


const std::complex<double> I (0,1);

void write (std::vector<    std::vector< std::complex<double>>   >  storage)
{
    std::ofstream out_file("store_serial.dat", std::ios::out);
    int T = storage.size();
    int N = storage[0].size();
    for (int t=0; t < T; ++t){
        for (int i=0; i < N; ++i)
            out_file << std::real(storage[t][i]) << "\t";

        out_file << "\n";
        for (int i=0; i < N; ++i)
            out_file << std::imag(storage[t][i]) << "\t";

        out_file << "\n";
    }
}

int main (int argc, char** argv)
{
    const int N = 200;

    const double L  = 1;
    const double y0 = 0;
    const double x0 = -0.5;

    const double dt = 1e-3;

    const double tmax = 2;

    std::vector<std::complex<double>> locations;
    std::vector<std::complex<double>> locations2;
    std::vector<double> circulations;

    double xp;
    for (int j=0; j<N; ++j){
        xp = x0+(j-x0)/N;
        locations.push_back(xp+I*y0);
        locations2.push_back(xp+I*y0);
        circulations.push_back(1.0/N);//-4*xp/std::sqrt(1-4*xp*xp)/N);
    }

    int i = 0;
    double t=0;
    const std::complex<double> i_2pi (0,-1.0/2/M_PI);


    std::vector<    std::vector< std::complex<double>>   > storage;
    storage.push_back(locations);

    while(t<=tmax){
        for(int j=0; j < N; ++j){
            std::complex<double> V = 0;
            std::complex<double> Z = locations[j];
            for (int n=0; n < N; ++n){
                if (n==j){
                    continue;
                }
                V += circulations[n]/(Z-locations[n]);
            }
            V *= i_2pi;
            locations2[j] += dt*std::conj(V);
        }

        locations = locations2;

        if (i%100 == 0)
            storage.push_back(locations);

        t = dt*i++;
    }

    write(storage);

    return 0;
}
