#include <iostream>
#include <cmath>
using namespace std;
double f(double x){
    return sin(x);
}

double f_(double dx, double x){
    return dx/6*(f(x)+ 4*f(x+dx/2)+ f(x+dx));
}

int main(){
    //integration limits
    double a = 0;
    double b = M_PI;

    int N; //number of bins
    cout << "Input the number of integration bins:\n";
    cin >> N;

    //compute dx (delta x)
    double dx = (b-a)/N;

    double out = 0;
    //for every bin
    for (int i=0; i < N; i++){
        // b = a + n*dx
        // add each bin to the total
        out += f_(dx,a+i*dx);
    }
    //create a conflict to experiment with git hub
    cout << "The integral of sin(x) from 0 to pi, approximated by the Simpson rule with " << N << " bins is: " << out;
};
