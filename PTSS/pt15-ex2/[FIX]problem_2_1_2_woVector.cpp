//Write a program allocating an array of length 10 and let the user provide an undetermined
//number of values (limited to 10) from standard input. Normalise the
//loaded sequence so that the sum is 1. Print out the normalised sequence in reverse
//order

#include <iostream> //cin, cout, getline
#include <stdlib.h> //atof

using namespace std;

int main(){
    int length = 1;
    double *old = new double[length];
    //get the input
    cout    << "Enter a sequence of numbers! \n"
            << "To add the next number press <Enter>. \n"
            << "To end the sequence press <Enter> twice. \n";

    string inp;
    getline(cin, inp);
    if(inp!=""){
            old[0] =  atof(inp.c_str());
    }
    while (inp!="") {
        ++length;
        double *neu = new double[length];
        for(int i=0; i < length-1; i++){
            cout << "old " << i << " " << old[i] <<endl;
            neu[i]=old[i];
            cout << "new " << i << " " << neu[i] <<endl;
        }
        getline(cin, inp);
        if (inp==""){break;}

        neu[length-1] = atof(inp.c_str());

        double *old = new double[length+1];
        for(int i=0; i < length; i++){
            cout << "neu " << i << " " << neu[i] << endl;
            old[i]=neu[i];
            cout << "old2 " << i << " " << old[i] << endl;
        }
    }

    //sum up
    double sum = 0;
    for (int i=0; i < length; i++){
        sum += old[i];
    }

    //print normalised
    for (int i=length-1; i >= 0; i--){
        cout << old[i]/sum << "\n";
    }

    return 0;
}
