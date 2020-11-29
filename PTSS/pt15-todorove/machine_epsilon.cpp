#include <iostream>
#include <limits>
#include <stdio.h>
#include <iomanip>

using namespace std ;

float compute_float(){

    float eps = 1.0f;
    float one = 1.0f;
    float a;

    do{
        eps /= 2;
        a = one + eps;
    }
    while(a > one);

    return eps*2;
}

double compute_double(){

    double eps = 1.0;
    double one = 1.0;
    double a;

    do{
        eps /= 2;
        a = one + eps;
    }
    while(a > one);

    return eps*2;
}

long double compute_longDouble(){

    long double eps = 1.0;
    long double one = 1.0;
    long double a;

    do{
        eps /= 2;
        a = one + eps;
    }
    while(a > one);

    return eps*2;
}


int main ( )
{
    float feps = compute_float();
    double deps = compute_double();
    long double leps = compute_longDouble();
    cout << setprecision(100);
    cout << "Machine precision on this machine: \n" << endl;
    cout << "\t \tComputed: \t\tReferenced:" << endl;
    cout << "Float: \t \t" << feps << "\t \t" << numeric_limits<float>::epsilon() << endl;
    cout << "Double: \t" << deps << "\t \t" << numeric_limits<double>::epsilon() << endl;
    cout << "LongDouble: \t" << leps * 1e+100 << "-100\t" << numeric_limits<long double>::epsilon() * 1e+100 << "-100" << endl;

    return 0 ;
}
