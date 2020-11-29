// Mid-point approximation of the integral
// parallel implementation
// author: etodorov

#include <iostream> //cout
#include <cmath>    // sqrt, log
#include <thread>   // thread
#include <functional> //ref
#include "timer.hpp"
#include "mingw.thread.h" //thread for MinGW
using namespace std;

double riemannSum_parallel (double a,
                            double b,
                            double (*f)(double x),
                            int N,
                            double& S){

    double dx = (b-a)/N;
    S = 0;

    for(int i=1; i<=N; ++i){
            S += f(a+i*dx-dx/2.0)*dx;
    }
    return S;
}


double f ( double x){
    return sqrt(x)*log(x);
}

double run(const int threadN){
// integrate sqrt(x)*ln(x) from 1 to 4 in N steps
// parallel implementation
    double a = 1.0;
    double b = 4.0;
    int N = 3000000;
    double output = 0;

    double Ss[threadN];
    thread threads[threadN];
    int threadStep = N/threadN; //be careful with odd numbers
    double dx         = (b-a)/N;

    timer t;
    t.start();


    for(int i = 0; i < threadN; ++i){
        threads[i] = thread( riemannSum_parallel,
                            a + i*threadStep*dx,    //thread a
                            a + (i+1)*threadStep*dx,//thread b
                            f,
                            threadStep,             //thread N
                            ref(Ss[i]) );           //get output
    }

    for(thread& t : threads){
        t.join();
    }

    for(double S : Ss){
        output += S;
    }

    t.stop();
    double ti;
    ti = 1000*t.get_timing();

    return ti;
}

int main(){
    const int threadNs[] = {1,2,3,4,5,6,8,10,20,100};
    const int N = 100;

    for(int threadN : threadNs){
        double total = 0;
        double maximum = 0;
        double minimum = 10000;
        double ti;
        for(int i=0; i < N; ++i){
            ti = run(threadN);
            total += ti;
            if (ti > maximum){maximum=ti;}
            if (ti < minimum){minimum=ti;}
        }
        cout<< threadN << " thread: \n"
            << "Average: " << total/N << endl
            << "Maximum: " << maximum << endl
            << "Minimum: " << minimum << endl << endl;
    }

    return 0;
}
