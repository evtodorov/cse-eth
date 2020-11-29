#include <iostream> //cout
#include <chrono>
#include <vector>   // vector, push_back
#include <cstdlib>  //size_t
#include <ratio>   //nano
using namespace std;
using namespace chrono;
int main(){
    const int Nmax = 3000000;
    char xs[cachemax];

    vector<double> time;
    vector<size_t> length;

    time_point<high_resolution_clock> t0, t1;

    bool running = 1;
    while (running){
        cur_xs =
        t0 = high_resolution_clock::now();
        for( char x : xs){
            xs = xs+xs+xs;
        }
        t1 = high_resolution_clock::now();
        duration<double, nano> t = t1-t0;

        cout << xs.size() << "\t" << t.count() << endl;
        time.push_back(t.count());
        length.push_back(xs.size());

        for( char x : xs){
            xs.push_back(x);
        }

        if (xs.size() > 3000000){
            running = 0;
        }

    }


    return 0;
}
