#include <iostream>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
extern "C" void dsyev_ ( char*, char*, int*, double*, int*, double*, double*, int*, int*);

int main(int argc, char** argv)
{
    int N = argc < 2 ? 16 : std::stoi(argv[1]);

    //initialize matrix
    double A[N*N];
    //FORTRAN is COLUMN major!!! (doesn't really matter for SY)
    for(int i=0; i < N*N; ++i){
        if(i%(N+1)==0)
            A[i] = 2;
        else if(i%(N+1)==1 || i%(N+1)==N)
            A[i] = -1;
        else
            A[i] = 0;
    }

    for(unsigned i=0; i < N; ++i){
        for(int j=0; j < N; ++j){
            std::cout << A[j*N + i] << " ";
        }
        std::cout << "\n";
    }


    char jobz = 'V';
    char uplo = 'U';

    double W[N]; //eigenvalues
    double lwork0;
    int info;
    int minOne = -1;
    dsyev_(&jobz, &uplo, &N, A, &N, W, &lwork0, &minOne, &info);

    int lwork = lwork0;
    double work[lwork];
    dsyev_(&jobz, &uplo, &N, A, &N, W, work, &lwork, &info);
    std::cout << "Numerical: \tAnalytical:" <<std::endl;
    std::cout.precision(8);
    for(int i=0; i < N; ++i){
        std::cout << W[i] << "\t" << std::sqrt(2.0-2.0*std::cos(M_PI*(i+1.0)/(N+1.0))) << std::endl;
    }

/*    for(unsigned i=0; i < N; ++i){
        for(int j=0; j < N; ++j){
            std::cout << A[i*N + j] << " ";
        }
        std::cout << "\n";
    }*/
std::cout << info;
std::cout << work[0];
    return 0;
}
