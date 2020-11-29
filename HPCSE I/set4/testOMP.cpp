#include "timer.hpp"
#include <iostream>
#include <omp.h>
#include <cstddef>
using namespace std;

int main ()
{
    const size_t N = 100000;
        cout << "before array";

    double A[N*N];

    timer t;
    t.start();
    cout << "before";
    int i;
    #pragma omp parallel for reduction(+:sum)
    for ( i=0; i < N; ++i){
        for (int j=0;j < N; ++j){
            A[i*N+j] = i*j+5%(j-i);
        }
        if (i%100==0){
                cout << omp_get_num_threads();
        }
    }
    t.stop();
    cout << endl << omp_get_max_threads() << endl;
    cout << t.get_timing() << endl;

    return 0;
}
