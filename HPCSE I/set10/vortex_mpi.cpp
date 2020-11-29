#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <complex>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

#include <mpi.h>

const std::complex<double> I (0,1);

void write (std::vector<    std::vector< std::complex<double>>   >  storage, int rank)
{
    std::string fname = "store_mpi_rank_";
    fname += std::to_string(rank);
    fname += ".dat";
    std::ofstream out_file(fname, std::ios::out);
    int T = storage.size();
    int N = storage[0].size();
    for (int t=0; t < T; ++t){
        for (int i=0; i < N; ++i)
            out_file << std::real(storage[t][i]) << "\t";

        out_file << std::endl;
        for (int i=0; i < N; ++i)
            out_file << std::imag(storage[t][i]) << "\t";

        out_file << std::endl;
    }
    out_file.close();
}



int main (int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    const int N = argc > 1 ? std::stoi(argv[1]) : 200;
    const int M = N/size;

    const double L  = 1;
    const double y0 = 0;
    const double x0 = -.5;

    const double dt = 1e-3;

    const double tmax = 0.1;

    std::vector<std::complex<double>> locations_private;
    std::vector<std::complex<double>> locations_alien;
    std::vector<std::complex<double>> locations_alien_new;
    std::vector<std::complex<double>> velocities;
    std::vector<double> circulations;


    double xp;
    for (int j=rank*M; j<(rank+1)*M; ++j){
        xp = x0+(j+0.5)/N;
        locations_private.push_back(xp+I*y0);
        locations_alien.push_back(0);
        locations_alien_new.push_back(0);
        velocities.push_back(0);
    }

    for (int j=0; j<N; ++j){
        xp = x0+(j+0.5)/N;
        circulations.push_back(1.0/N);//-4*xp/std::sqrt(1-4*xp*xp)/N);
    }

    int i = 0;
    double t=0;
    const std::complex<double> i_2pi (0,-1.0/2/M_PI);


    std::vector<    std::vector< std::complex<double>>   > storage;
    storage.push_back(locations_private);

    MPI_Barrier(MPI_COMM_WORLD);
    auto t0 = std::chrono::high_resolution_clock::now();

    while(t<=tmax){
        //send your own particles and receive alien particles
        int alien_to_receive_from = (size + rank - 1) % size;
        int alien_to_send_to = (rank + 1) % size;
        MPI_Request request_send, request_recv;
        MPI_Status status_send, status_recv;
        MPI_Isend(&locations_private[0], M, MPI_DOUBLE_COMPLEX, alien_to_send_to, 0,MPI_COMM_WORLD, &request_send);
        MPI_Irecv(&locations_alien[0], M, MPI_DOUBLE_COMPLEX, alien_to_receive_from,0, MPI_COMM_WORLD, &request_recv);

        //do your own particles
        std::complex<double> V;
        std::complex<double> Z;
        for(int j=0; j < M; ++j){
            V = 0;
            Z = locations_private[j];
            for (int n=0; n < M; ++n){
                if (n==j){
                    continue;
                }
                V += circulations[rank*M+n]/(Z-locations_private[n]);
            }
            velocities[j] = V;
        }
        //end receiving the first of alien particles
        MPI_Wait(&request_recv, &status_recv);
        MPI_Wait(&request_send, &status_send);

        //for each other process
        for (int q=1; q < size; ++q){
            int alien_current = alien_to_receive_from;
            alien_to_receive_from = (size - q + rank - 1) % size ;
            alien_to_send_to = (rank + q + 1) % size;

            //start receiving the next alien particles
            if (q < size - 1){
                MPI_Isend(&locations_private[0], M, MPI_DOUBLE_COMPLEX, alien_to_send_to, q,MPI_COMM_WORLD, &request_send);
                MPI_Irecv(&locations_alien_new[0], M, MPI_DOUBLE_COMPLEX, alien_to_receive_from, q, MPI_COMM_WORLD, &request_recv);
            }

            //calculate for alien particles
             for(int j=0; j < M; ++j){
                V = 0;
                Z = locations_private[j];
                for (int n=0; n < M; ++n){
                    V += circulations[alien_current*M+n]/(Z-locations_alien[n]);
                }
                velocities[j] += V;
            }

            //end receiving the next alien particles
            if (q < size - 1){
                MPI_Wait(&request_recv, &status_recv);
                MPI_Wait(&request_send, &status_send);
                locations_alien = locations_alien_new;
            }
        }

        for (int i=0; i < M; ++i)
            locations_private[i] += dt*std::conj(i_2pi*velocities[i]);


        //if (i%100 == 0){
            //storage.push_back(locations_private);


        //}
        t = dt*i++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0){
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> t = t1-t0;
        std::cout << size << "\t" << N << "\t" << t.count() << std::endl;
    }
    //write(storage, rank);

    MPI_Finalize();
    return 0;
}
