#include <iostream> //cout, endl
#include <cmath>    //abs
#include <vector>   //vector
#include <algorithm>//swap, copy
#include <string>   //stod, stoi
#include <omp.h>

#include "timer.hpp"

class Problem{
///assuming M=N, dx=dy=dr
private:
    const double dt_;
    const int N_;
    const int totN_;
    const double min_;
    const double max_;
    const double dr_;
    const double nu_;
    std::vector<double> mesh_;
    std::vector<double> store_;

public:
    Problem(const double dt, const int N, double min, double max, double D)
        : dt_(dt), N_(N), totN_(N*N), min_(min), max_(max), dr_((max-min)/(N-1)), nu_(D*dt/dr_/dr_)
    {
        mesh_.resize(N*N,0);
        store_.resize(N*N,0);
    }
    void setInitConditions(double val){
        ///central source
        for(int i = 0; i < N_; ++i){
            for(int j = 0; j < N_; ++j){
                if( std::abs(min_+i*dr_) < 0.5 && std::abs(min_+j*dr_) < 0.5){
                    mesh_[i*N_+j] = val;
                }
            }
        }
        std::copy(mesh_.begin(),mesh_.end(),store_.begin());
    }
    void printMesh(int abbr=1, int precision=3){
        ///print every abbr element
        int n = N_/abbr;
        std::cout.precision(precision);
        std::cout << "Mesh:" << std::endl;
        for(int i=0;i < n; ++i){
            for (int j=0; j < n; ++j){
                std::cout << mesh_[abbr*N_*i+j*abbr] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void printStore(int abbr=1, int precision=3){
        ///print every abbr element
        int n = N_/abbr;
        std::cout.precision(precision);
        std::cout << "Store:" << std::endl;
        for(int i=0;i < n; ++i){
            for (int j=0; j < n; ++j){
                std::cout << store_[abbr*N_*i+j*abbr] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    void step(){
        int i;
        #pragma omp parallel for
       /* for (i=0;i<totN_;++i){
            mesh_[i] =  store_[i] + nu_ * (
                        (i%N_==0     ?   0   :   store_[i-1]) +
                        (i%N_==N_-1  ?   0   :   store_[i+1]) +
                        (i<N_        ?   0   :   store_[i-N_])+
                        (i>totN_-N_  ?   0   :   store_[i+N_])-
                        4*store_[i]);

        }*/
        for(i = 0; i < N_; ++i) {
            for(int j = 0; j < N_; ++j) {
                mesh_[i*N_ + j] = store_[i*N_ + j] +
                nu_
                *
                (
                 (j == N_-1 ? 0. : store_[i*N_ + (j+1)])
                 +
                 (j == 0    ? 0. : store_[i*N_ + (j-1)])
                 +
                 (i == N_-1 ? 0. : store_[(i+1)*N_ + j])
                 +
                 (i == 0    ? 0. : store_[(i-1)*N_ + j])
                 -
                 4.*store_[i*N_ + j]
                 );
            }
        }//WHY IS THIS FASTER????*/

        #pragma omp barrier     //wait until all values are written
        #pragma omp master      //execute swap only in master thread
        std::swap(mesh_,store_);
        #pragma omp barrier     //make sure swap is finished before continuing
    }
    void update(){
        std::copy(store_.begin(),store_.end(),mesh_.begin());
    }

};

int main(int argc, char* argv[]){

    if (argc < 3){
        std::cout << "diffusion_mp cores N dt" << std::endl;
        return 0;
    }

    const double dt = std::stod(argv[3]);
    const int N     = std::stoi(argv[2]);
    const int cores = std::stoi(argv[1]);

    omp_set_num_threads(cores);

    timer t;
    const double tmax = 10000*dt;
    const int D = 1;
    Problem diffusion = Problem(dt,N,-1.0,1.0,D);

    diffusion.setInitConditions(1.0);
    t.start();
    for(int i=1; i <= tmax/dt; ++i){
        diffusion.step();
    }
    t.stop();
    std::cout << "MaxC\tCurC\tN\ttime \n";
    std::cout << omp_get_max_threads() << "\t" << cores << "\t" << N << "\t" << t.get_timing() << std::endl;
    return 0;
}
