#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <complex>
#include <string>
#include <vector>
#include <cmath>


const std::complex<double> I (0,1);

void write (std::vector<  std::vector<double> >  storageX, std::vector<  std::vector<double> >   storageY)
{
    std::ofstream out_file("store_double.dat", std::ios::out);
    int T = storageX.size();
    int N = storageX[0].size();
    for (int t=0; t < T; ++t){
        for (int i=0; i < N; ++i)
            out_file << storageX[t][i] << "\t";

        out_file << "\n";
        for (int i=0; i < N; ++i)
            out_file << storageY[t][i] << "\t";

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

    std::vector<double> x;
    std::vector<double> x2;
    std::vector<double> y;
    std::vector<double> y2;
    std::vector<double> circulations;

    double xp;
    for (int j=0; j<N; ++j){
        xp = x0+(j-x0)/N;
        x.push_back(xp);
        x2.push_back(xp);
        y.push_back(y0);
        y2.push_back(y0);
        circulations.push_back(1.0/N);//-4*xp/std::sqrt(1-4*xp*xp)/N);
    }

    int i = 0;
    double t=0;
    const double i_2pi = 0.5/M_PI;


    std::vector<    std::vector<double>   > storageX;
    std::vector<    std::vector<double>   > storageY;
    storageX.push_back(x);
    storageY.push_back(y);

    while(t<=tmax){
        for(int j=0; j < N; ++j){
            double Vx = 0;
            double Vy = 0;
            double X = x[j];
            double Y = y[j];
            for (int n=0; n < N; ++n){
                if (n==j){
                    continue;
                }
                double dx = X - x[n];
                double dy = Y - y[n];
                double dr2 = dx*dx + dy*dy;

                Vx += circulations[n]*dx/dr2;
                Vy -= circulations[n]*dy/dr2;
            }
            Vx *= i_2pi;
            Vy *= i_2pi;
            x2[j] += dt*Vx;
            y2[j] += dt*Vy;
        }

        x = x2;
        y = y2;

        if (i%100 == 0){
            storageY.push_back(y);
            storageX.push_back(x);
        }

        t = dt*i++;
    }

    write(storageX,storageY);

    return 0;
}
