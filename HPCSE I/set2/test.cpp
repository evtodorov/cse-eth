#include <iostream>
#include <utility>
using namespace std;



void f(int arr1[3],int arr2[3]){
    cout << "In func before swap: " << endl << "arr1: \n" << arr1[0] << arr1[1] << arr1[2] << "\n arr2: \n" << arr2[0] << arr2[1] << arr2[2] << endl;
    swap(arr1,arr2);
    cout << "In func after swap: " << endl << "arr1: \n" << arr1[0] << arr1[1] << arr1[2] << "\n arr2: \n" << arr2[0] << arr2[1] << arr2[2] << endl;
}

int main(){
    int arr1[10] = {0,1,2};
    int arr2[10] = {10,11,12};

    cout << "Before: " << endl << "arr1: \n" << arr1[0] << arr1[1] << arr1[2] << "\n arr2: \n" << arr2[0] << arr2[1] << arr2[2] << endl;

    f(arr1,arr2);

    cout << "After func before swap: " << endl << "arr1: \n" << arr1[0] << arr1[1] << arr1[2] << "\n arr2: \n" << arr2[0] << arr2[1] << arr2[2] << endl;
    swap(arr1,arr2);
    cout << "After func after swap: " << endl << "arr1: \n" << arr1[0] << arr1[1] << arr1[2] << "\n arr2: \n" << arr2[0] << arr2[1] << arr2[2] << endl;
    return 0;

}
