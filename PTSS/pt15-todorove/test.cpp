#include <iostream>
#include <typeinfo>

using namespace std;

int main(){
    float x = 1.0;
    cout << typeid(x/1.0).name() << endl;
    cout << sizeof(x/1.0) << endl;
    cout << typeid(x/2).name() << endl;
    cout << sizeof(x/2) << endl;
    cout << typeid(1/1.0f).name() << endl;
    cout << sizeof(1/1.0f) << endl;
    cout << typeid(1.0/1.0f).name() << endl;
    cout << sizeof(1.0/1.0f) << endl;
    cout << typeid(1.0f/1.0).name() << endl;
    cout << sizeof(1.0f/1.0) << endl;
    return 0;
}
