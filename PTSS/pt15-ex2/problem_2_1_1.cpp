//Write a program allocating an array of length 10 and let the user provide an undetermined
//number of values (limited to 10) from standard input. Normalise the
//loaded sequence so that the sum is 1. Print out the normalised sequence in reverse
//order

#include <iostream> //cin, cout, getline
#include <stdlib.h> //atof

using namespace std;

int main(){

    const int max_length = 10;
    int cur_length = 0;
    double arr[max_length];

    //get the input
    cout    << "Enter a sequence of numbers! \n"
            << "Maximum length of sequence - ten numbers. \n"
            << "To add the next number press <Enter>. \n"
            << "To end the sequence press <Enter> twice. \n";
    for (int i=0; i < max_length; i++){
        string inp;
        getline(cin, inp);
        if (inp==""){break;}
        arr[i] = atof(inp.c_str());
        ++cur_length;
    }

    //sum up
    double sum = 0;
    for (int i=0; i < cur_length; i++){
        sum += arr[i];
    }

    //print normalised
    for (int i=cur_length-1; i >= 0; i--){
        cout << arr[i]/sum << "\n";
    }

    return 0;
}
