// Mid-point approximation of the integral
// parallel implementation
// author: etodorov

#include <iostream> //cout
#include <cmath>    // sqrt, log
#include <algorithm> // max
#include <thread>   // thread
#include <functional> //ref
#include "timer.hpp"
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

int main(){
// integrate sqrt(x)*ln(x) from 1 to 4 in N steps
// parallel implementation
    double a = 1.0;
    double b = 4.0;
    int N = 3000000;
    double output = 0;

    cout << "Integrate sqrt(x)*ln(x) from " << a
         << " to " << b << " in " << N << " steps" << endl;

    size_t const nthreads = max(1u,thread::hardware_concurrency());

    double Ss[threadN];
    thread threads[threadN];
    int threadStep = N/threadN; //be careful with odd numbers
    double dx         = (b-a)/N;
    cout << "Using " << threadN << " threads." << endl;

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
    cout.precision(15);
    cout << "Answer: " << output
         <<" in " << 1000*t.get_timing() << " ms. " <<endl;

    return 0;
}
