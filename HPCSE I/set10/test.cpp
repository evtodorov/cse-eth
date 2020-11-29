#include <iostream>
#include <mpi.h>
#include <vector>
int main(int argc, char** argv)
{/*
    int size = 20;
    int sender;
    for (int rank = 0; rank < size; ++rank){
        for (int q = 1; q < size; ++q){
            sender = (size - q + rank) % size;
            std::cout << sender <<" ";
        }
        std::cout << std::endl;
    }
*/
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Request request, request2;
    MPI_Status status;
    std::vector<int> out;
    out.reserve(5);
    if(rank==0){
        std::vector<int> in = {1,1,1,1,1};
        MPI_Isend(&in[0], 6, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
        MPI_Isend(&in[0], 5, MPI_INT, 2, 1, MPI_COMM_WORLD, &request);
        MPI_Isend(&in[0], 5, MPI_INT, 3, 1, MPI_COMM_WORLD, &request);
        MPI_Irecv(&out[0], 6, MPI_INT, 1, 2, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }
    else if (rank==1){
        std::vector<int> in = {2,2,2,2,2};
        MPI_Isend(&in[0], 6, MPI_INT, 0, 2, MPI_COMM_WORLD, &request);
        MPI_Irecv(&out[0], 6, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }
    else{
        MPI_Irecv(&out[0], 6, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }
    std::cout << "I " << rank << " recieved " << out[1] << std::endl;
    MPI_Finalize();
    return 0;
}
