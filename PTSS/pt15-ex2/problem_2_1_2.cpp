//Write a program allocating an array of length 10 and let the user provide an undetermined
//number of values (limited to 10) from standard input. Normalise the
//loaded sequence so that the sum is 1. Print out the normalised sequence in reverse
//order

#include <iostream> //cin, cout, getline
#include <stdlib.h> //atof
#include <vector> //vector
using namespace std;

int main(){
    vector<double> arr;
    //get the input
    cout    << "Enter a sequence of numbers! \n"
            << "To add the next number press <Enter>. \n"
            << "To end the sequence press <Enter> twice. \n";


    while (1) {
        string inp;
        getline(cin, inp);
        if(inp==""){
            break;
        }
        arr.push_back(atof(inp.c_str()));
    }

    //sum up
    double sum = 0;
    vector<double>::size_type length = arr.size();
    for (int i=0; i < length; i++){
        sum += arr[i];
    }

    //print normalised
    for (int i=length-1; i >= 0; i--){
        cout << arr[i]/sum << "\n";
    }

    return 0;
}
