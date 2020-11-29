#include <iostream> //cout
#include <thread>   //
//#include "mingw.thread.h"   //threads for mingw
#include <cmath> //abs
#include <fstream> //open, close
using namespace std;
template<const int cols>
void printarr(double arr[][cols], int sizeX, int sizeY, char fname[]){
    ofstream f;
    f.open(fname);
    for(int i=0; i < sizeX; i+=1){
        for(int j=0; j<sizeY; j+=1){
            f << arr[i][j] << ", ";
        }
        f << endl;
    }
    f.close();
}
template<const int cols>
inline void mesh_init(double mesh[][cols],
                int resX, int resY,
                double xmin, double ymin,
                double dx, double dy){

    double xi, yj;
    for(int i=0; i < resX; ++i){
        xi = xmin + i*dx;
        //C++ is row-major, so last index - innermost loop
        for(int j=0; j<resY; ++j){
            yj = ymin + j*dy;

            //initial conditions
            if(abs(yj) <= 0.5 && abs(xi) <= 0.5){
                mesh[i][j] = 1;
            }
            else{
                mesh[i][j] = 0;
            }
        }
    }
}

template<const int cols>
inline void mesh_update(double mesh[][cols],
                int resX, int resY,
                double dx, double dy,
                double D, const double dt, int N){

    //create old to contain copy of mesh + BC values
    double old[resX+2][resY+2]; //init to 0

    //copy mesh to old
    for(int i=0; i < resX+2; ++i){
        for(int j=0; j<resY+2; ++j){
            if(i-1>=0 && i<=resX && j<=resY && j-1>=0){
                old[i][j]=mesh[i-1][j-1];
            }
            else{
                old[i][j]=0;
            }
        }
    }

    //update mesh
    for(int i=1; i <= resX; ++i){
        //C++ is row-major, so last index - innermost loop
        for(int j=1; j<=resY; ++j){
            mesh[i-1][j-1]+= dt*D*(
                        (old[i-1][j]+old[i+1][j]-2*old[i][j])/dx/dx +
                        (old[i][j-1]+old[i][j+1]-2*old[i][j])/dy/dy
                               );

        }
    }
}



int main(){
    //parameters
    double D = 1;
    double xmin = -1;
    double ymin = -1;
    double xmax = 1;
    double ymax = 1;

    //set 1
    const int resX = 128u;
    const int resY = 128u;
    const double dt = 1e-5; //add some speed?

    //set 2
//    const int resX = 256;
//    const int resY = 256;
//    double dt = 1e-6;

    //set3
//    const int resX = 1024u;
//    const int resY = 1024u;
//    double dt = 1e-8;

    double dx = (xmax-xmin)/(resX-1);
    double dy = (ymax-ymin)/(resY-1);

    //initialize mesh
    double mesh[resX][resY];

    mesh_init(mesh,resX,resY,xmin,ymin,dx,dy);

    printarr(mesh,resX,resY,"t=0.csv");

    double tmax = 2;
    double t = 0;
    int N = 0;

    while(t <= tmax){


        mesh_update(mesh,resX,resY,dx,dy,D,dt,N);
        if(N%1000==0){cout << t << endl;}
        if(N==50000000){printarr(mesh,resX,resY,"t=5e-1.csv");}
        if (N==100000000){printarr(mesh,resX,resY,"t=1.csv");}
        t += dt; ++N;
    }

    printarr(mesh,resX,resY,"t=2.csv");

    return 0;
}
