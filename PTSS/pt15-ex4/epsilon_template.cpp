#include <iostream> //cout
#include <limits>
using namespace std;

template<typename T>
void epsilon(){
    T one = 1;
    T eps = 1;

    while (one+eps!=one){
        eps /= 2;
    }

    cout << "Computed: " << eps*2 << endl << "From <limits>: " << numeric_limits<T>::epsilon() << endl;
}

int main(){

    cout << "For <float>: " << endl; epsilon<float>();
    cout << "For <double>: " << endl; epsilon<double>();
    cout << "For <long double>: " << endl; epsilon<long double>();

    return 0;
}
