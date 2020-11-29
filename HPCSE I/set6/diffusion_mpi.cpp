#include <iostream> //cout, endl
#include <cmath>    //abs
#include <vector>   //vector
#include <algorithm>//swap, copy
#include <string>   //stod, stoi
#include <mpi.h>
#include <cassert>
#include "timer.hpp"


class Problem{
///assuming M=N, dx=dy=dr
private:
    const int size_;
    const int rank_;
    const double dt_;
    int N_; ///local number
    const int totN_; ///total number
    const double min_;
    const double max_;
    const double dr_;
    const double nu_;
    std::vector<double> mesh_;
    std::vector<double> store_;
    std::vector<double> leftbnd_;
    std::vector<double> rightbnd_;
public:
    Problem(const double dt, const int N, double min, double max, double D, int size, int rank)
        : dt_(dt),
          N_(N),
          totN_(N*size),
          min_(min),
          max_(max),
          dr_((max-min)/(N-1)),
          nu_(D*dt/dr_/dr_),
          size_(size),
          rank_(rank)
    {
        mesh_.resize(N*totN_,0);
        store_.resize(N*totN_,0);
        leftbnd_.resize(totN_,0);
        rightbnd_.resize(totN_,0);
    }

    void setInitConditions(double val){
        ///central source
        for(int i = 0; i < N_; ++i){
            for(int j = 0; j < totN_; ++j){
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


    void join()
    ///combine the mesh_loc_ and store_loc_ back into mesh_ and store_
    {
        //TODO: join
    }

    void step()
    {
        //start sending
        MPI_Request req[4];
        MPI_Status stat[4];
    if(size_>1){
        if( rank_%2==0){
            //1st send to the left, then receive from the left
            if (rank_==0){
                 std::fill(leftbnd_.begin(), leftbnd_.end(),0); //leftmost
                 req[0] = MPI_REQUEST_NULL;
                 req[1] = MPI_REQUEST_NULL;
            }
            else{
                MPI_Isend(&store_[0],totN_,MPI_DOUBLE,rank_-1,0,MPI_COMM_WORLD,&req[0]);
                MPI_Irecv(&leftbnd_[0],totN_,MPI_DOUBLE,rank_-1,1,MPI_COMM_WORLD,&req[1]);
            }
            //now send to the right and then receive from the right
            MPI_Isend(&store_[(N_-1)*totN_],totN_,MPI_DOUBLE, rank_+1,2,MPI_COMM_WORLD,&req[2]);
            MPI_Irecv(&rightbnd_[0],totN_,MPI_DOUBLE,rank_+1,3,MPI_COMM_WORLD,&req[3]);

        }
        else{
            //receive from right, then send to right)
            if ( rank_== size_ - 1){
                std::fill(rightbnd_.begin(),rightbnd_.end(),0); //rightmost
                req[0] = MPI_REQUEST_NULL;
                req[1] = MPI_REQUEST_NULL;
            }
            else{
                MPI_Irecv(&rightbnd_[0],totN_,MPI_DOUBLE,rank_+1,0,MPI_COMM_WORLD,&req[0]);
                MPI_Isend(&store_[(N_-1)*totN_],totN_,MPI_DOUBLE,rank_+1,1,MPI_COMM_WORLD,&req[1]);
            }
            //receive from left, send to left
            MPI_Irecv(&leftbnd_[0],totN_,MPI_DOUBLE,rank_-1,2,MPI_COMM_WORLD,&req[2]);
            MPI_Isend(&store_[0],totN_,MPI_DOUBLE,rank_-1,3,MPI_COMM_WORLD,&req[3]);
        }


        //do the core
        for(int i = 1; i < N_-1; ++i) {
            for(int j = 0; j < totN_; ++j) {

            mesh_[i*totN_ + j] = store_[i*totN_ + j] +
                nu_
                *
                (
                 (j == totN_-1 ? 0. : store_[i*totN_ + (j+1)])
                 +
                 (j == 0    ? 0. : store_[i*totN_ + (j-1)])
                 +
                 store_[(i+1)*totN_ + j]
                 +
                 store_[(i-1)*totN_ + j]
                 -
                 4.*store_[i*totN_ + j]
                 );
            }
        }
    }
    else{
        for (auto& r : req){
            r = MPI_REQUEST_NULL;
        }
    }
        // complete receiving
        MPI_Waitall(4,req,stat);

        //do the boundaries
        //left
        for(int j = 0; j < totN_; ++j) {
            mesh_[j] = store_[j] +
                nu_
                *
                (
                 (j == totN_-1 ? 0. : store_[j+1])
                 +
                 (j == 0    ? 0. : store_[j-1])
                 +
                 store_[totN_ + j]
                 +
                 leftbnd_[j]
                 -
                 4.*store_[j]
                 );
        }
        //right
        --N_;
        for(int j = 0; j < totN_; ++j) {
            mesh_[N_*totN_ + j] = store_[N_*totN_ + j] +
                nu_
                *
                (
                 (j == totN_-1 ? 0. : store_[N_*totN_ + (j+1)])
                 +
                 (j == 0    ? 0. : store_[N_*totN_ + (j-1)])
                 +
                 rightbnd_[j]
                 +
                 store_[(N_-1)*totN_ + j]
                 -
                 4.*store_[N_*totN_ + j]
                 );
        }
        ++N_;

        std::swap(mesh_,store_);
    }

    void update(){
        std::copy(store_.begin(),store_.end(),mesh_.begin());
    }

};

int main(int argc, char* argv[]){

    MPI_Init(&argc, &argv);
    int size, rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2){
            if ( rank == 0){
                std::cout << "mpiexec -n #CORES diffusion_mpi N dt" << std::endl;
            }
        MPI_Finalize();
        return 0;
    }


    const double dt = std::stod(argv[2]);
    const int N     = std::stoi(argv[1])/size;
    const double tmax = 10000*dt;
    const int D = 1;

    const double totMin = -1.0;
    const double totMax = 1.0;

    double locMin = totMin + rank * (totMax-totMin)/size;
    double locMax = locMin + (totMax-totMin)/size;

    Problem diffusion(dt,N,locMin,locMax,D, size, rank);

    diffusion.setInitConditions(1.0);

//time only execution; use the root thread
    MPI_Barrier(MPI_COMM_WORLD);
    timer t;
    if (rank==1){
        t.start();
    }
    MPI_Barrier(MPI_COMM_WORLD);
    std::cout << "running " <<  rank << "\n";
    for(int i=1; i <= tmax/dt; ++i){
       diffusion.step();
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==1){
        t.stop();
        diffusion.join();
        std::cout << "Cores\tN\ttime \n";
        std::cout << size << "\t" << N*size << "\t" << t.get_timing() << std::endl;
    }

    MPI_Finalize();
    return 0;
}
