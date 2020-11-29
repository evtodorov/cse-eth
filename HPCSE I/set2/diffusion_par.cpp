#include <iostream> //cout
#include <thread>   //thread
#include <mutex>   //mutex
#include <cmath> //abs
#include <fstream> //open, close
#include <vector> //vector

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
void mesh_init(double mesh[][cols],
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


void par_update(double mesh[][128], double old[][130],
                    int limXstart,      //index in mesh for the first point (inclusive)
                    int limXend,        //index in mesh for the last point (inclusive)
                    int resY,
                    double dx, double dy,
                    double D, const double dt){
    double dmesh;
    for(int i=limXstart; i <= limXend; ++i){
        //C++ is row-major, so last index - innermost loop
        //mesh[i]=old[i-1]
        for(int j=0; j<=resY; ++j){
            dmesh = dt*D*(
                        (old[i-2][j-1]+old[i][j-1]-2*old[i-1][j-1])/dx/dx +
                        (old[i-1][j-2]+old[i-1][j]-2*old[i-1][j-1])/dy/dy
                               );
            mesh[i][j] += dmesh;

        }
    }
}


void mesh_update(double mesh[][128],
                int resX, int resY,
                double dx, double dy,
                double D, const double dt, int N, const int Nthreads){

    //create old to contain copy of mesh + BC values
    double old[130][128+2]; //init to 0

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
    mutex meshMutex;
    vector<thread> threads(Nthreads);
    //assume resX >> Nthreads
    int  len = resX/Nthreads;
    int limXstart, limXend;
    for(int i = 0; i < Nthreads-1; ++i){
        limXstart = i*len;
        limXend = (i+1)*len-1;
        threads[i] = thread(par_update,
                            mesh, old, resY,
                            limXstart,limXend,
                            dx,dy,D,dt);
    }
    threads[Nthreads-1] = thread(par_update,
                            mesh, old,
                            Nthreads-1*len,      //limXstart
                            Nthreads*len-1+resX%Nthreads, //limXend; add leftovers to last thread
                            dx,dy,D,dt);
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
    //const int resX = 1024u;
    //const int resY = 1024u;
    //double dt = 1e-8;

    double dx = (xmax-xmin)/(resX-1);
    double dy = (ymax-ymin)/(resY-1);

    //initialize mesh
    double mesh[resX][resY];

    mesh_init(mesh,resX,resY,xmin,ymin,dx,dy);

    printarr(mesh,resX,resY,"pt=0.csv");

    double tmax = 2;
    double t = 0;
    int N = 0;

    while(t <= tmax){


        mesh_update(mesh,resX,resY,dx,dy,D,dt,N,6);
        if(N%10000==0){cout << t << endl;}
        if(N==50000){printarr(mesh,resX,resY,"pt=5e-1.csv");}
        if (N==100000){printarr(mesh,resX,resY,"pt=1.csv");}
        t += dt; ++N;
    }

    printarr(mesh,resX,resY,"pt=2.csv");

    return 0;
}
