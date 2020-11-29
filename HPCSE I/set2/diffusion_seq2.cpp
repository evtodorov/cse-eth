#include <iostream> //cout
#include <thread>   //
//#include "mingw.thread.h"   //threads for mingw
#include <cmath> //abs
#include <fstream> //open, close
#include <utility> //swap
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
void print(double arr[][cols], int sizeX, int sizeY){

    for(int i=0; i < sizeX; i+=1){
        for(int j=0; j<sizeY; j+=1){
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
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
inline void mesh_update(double mesh[][cols], double old[][cols],
                int resX, int resY,
                double dx, double dy,
                double D, const double dt, int N){
    swap(mesh,old);
    //update mesh
    for(int i=1; i < resX-1; ++i){
        //C++ is row-major, so last index - innermost loop
        for(int j=1; j < resY-1; ++j){
            mesh[i][j]= old[i][j] + dt*D*(
                        (old[i-1][j]+old[i+1][j]-2*old[i][j])/dx/dx +
                        (old[i][j-1]+old[i][j+1]-2*old[i][j])/dy/dy
                               );

        }
    }
    //boundary conditions
        //corners
    mesh[0][0] = old[0][0] + dt*D*(
                        (old[1][0]-2*old[0][0])/dx/dx +
                        (old[0][1]-2*old[0][0])/dy/dy
                        );
    mesh[0][resY-1] = old[0][resY-1] + dt*D*(
                        (old[1][resY-1]-2*old[0][resY-1])/dx/dx +
                        (old[0][resY-2]-2*old[0][resY-1])/dy/dy
                        );
    mesh[resX-1][0] = old[resX-1][0] + dt*D*(
                        (old[resX-2][0]-2*old[resX-1][0])/dx/dx +
                        (old[resX-1][1]-2*old[resX-1][0])/dy/dy
                        );
    mesh[resX-1][resY-1] = old[resX-1][resY-1] +  dt*D*(
                        (old[1][resY-1]-2*old[0][resY-1])/dx/dx +
                        (old[0][resY-2]-2*old[0][resY-1])/dy/dy
                        );
        //sides
        for(int j=1; j < resY-1; ++j){
            int i = 0;
            mesh[i][j]= old[i][j] +  dt*D*(
                        (old[i+1][j]-2*old[i][j])/dx/dx +
                        (old[i][j-1]+old[i][j+1]-2*old[i][j])/dy/dy
                               );

        }
        for(int j=1; j < resY-1; ++j){
            int i = resX-1;
            mesh[i][j]= old[i][j] +  dt*D*(
                        (old[i-1][j]-2*old[i][j])/dx/dx +
                        (old[i][j-1]+old[i][j+1]-2*old[i][j])/dy/dy
                               );

        }
        for(int i=1; i < resX-1; ++i){
            int j = 0;
            mesh[i][j]= old[i][j] +  dt*D*(
                        (old[i-1][j]+old[i+1][j]-2*old[i][j])/dx/dx +
                        (old[i][j+1]-2*old[i][j])/dy/dy
                               );

        }
        for(int i=1; i < resX-1; ++i){
            int j = resY-1;
            mesh[i][j]= old[i][j] +  dt*D*(
                        (old[i-1][j]+old[i+1][j]-2*old[i][j])/dx/dx +
                        (old[i][j-1]-2*old[i][j])/dy/dy
                               );

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
    const int resX = 16u;
    const int resY = 16u;
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

    double tmax = 3*dt;
    double t = 0;
    int N = 0;

    //copy mesh to store
    double store[resX][resY];
    for(int i=0;i<resX;++i){
        for(int j=0;j<resX;++j){
            store[i][j] = mesh[i][j];
        }
    }
    while(t <= tmax){


        mesh_update(mesh,store,resX,resY,dx,dy,D,dt,N);
        cout << t;
        swap(mesh,store);
        print(mesh,resX,resY); print(store,resX,resY);
        if(N%1000==0){cout << t << endl;}
        if(N==50000){printarr(mesh,resX,resY,"t2=5e-1.csv");}
        if (N==100000000){printarr(mesh,resX,resY,"t=1.csv");}
        t += dt; ++N;
    }

    printarr(mesh,resX,resY,"t=2.csv");

    return 0;
}
