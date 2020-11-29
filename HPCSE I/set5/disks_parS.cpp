#include <iostream>
#include <array>
#include <random>
#include <cmath>
#include <cstddef>
#include <utility>
#include <omp.h>
#include <chrono>
using std::cout; using std::endl;


double PI = std::acos(-1);

template<size_t N, class T>
std::ostream& operator<<(std::ostream& os, const std::array<T,N> arr)
{

  for (auto a : arr){
    os << a << ", ";
  }

  return os;
}

template<size_t N, size_t M, class T>
std::ostream& operator<<(std::ostream& os, const std::array<std::array<T,N>,M> arr)
{
  for (auto a : arr){
    os << a << endl;
  }

  return os;
}

template<size_t N, class T>
std::array<T, N> operator+= (std::array<T, N> x, const std::array<T, N>& y )
{
    for (int i = 0; i < N; ++i)
    {
        x[i] += y[i];
    }
    return x;
}


struct Problem{
    std::mt19937 gen_p;
    std::mt19937 gen_a;

    static const int Nx = 10;
    static const int Ny = 15;
    const double L = 1.0;
    const double d0 = 0.5 * L / Nx;
    const double a = (L/Nx) - d0;

    typedef typename std::array<double, 2> Particle;
    typedef typename std::array<Particle, Nx*Ny> Particles;

    Particles particles;

    Problem () {
        hist.fill(0);
        gen_p = std::mt19937 (83457);
        gen_a = std::mt19937 (38954);
    }
    Problem (Particles state, int seed)
    {
        gen_p = std::mt19937 (4892378234%(17*seed));
        gen_a = std::mt19937 (3435543542%(31*seed));
        hist.fill(0);
        particles = state;
    }

    Particles IC ()
    ///initial conditions, honeycomb
    ///automatically sets the BC of the current instance
    {
        double dx = L/Nx;
        double dy = std::sqrt(3.)/2. * dx;
        for (int i = 0; i < Nx; ++i){
            for (int j = 0; j < Ny; ++j){

                particles[i*Ny+j][0] = (i+0.25+(j%2)/2.)*dx;
                particles[i*Ny+j][1] = (j+0.5)*dy;
            }
        }
        return particles;
    }


    std::uniform_int_distribution<> choose_p =
                std::uniform_int_distribution<>(0,Nx*Ny);

    inline double distance (double x1, double y1,
                            double x2, double y2) const
    {
        using std::abs;
        double x = ( abs(x1-x2) < L-abs(x1-x2) )
                                        ? ( x1 - x2 )
                                        : ( L - abs(x1-x2) );
        double y = ( abs(y1-y2) < L-abs(y1-y2) )
                                        ? ( y1 - y2 )
                                        : ( L - abs(y1-y2) );

        return std::sqrt(x*x+y*y);

    }

    inline double BC (double x) const
    {
        if ( x < 0 ) {
            x = L - x;
        }
        else if ( x > L){
            x = x - L;
        }
        else{
            x = x;
        }
        return x;
    }

    bool overlap (double x, double y, int currentParticle)
    /// check if the particle overlaps
    {
        for (auto& p : particles){
            if (p==particles[currentParticle]){continue;}
            if ( distance(x,y,p[0],p[1]) <= d0 )
            {
                return 1;
            }
        }
        return 0;
    }

    void sweep ()
    /// try to update on average every particle once
    {
        for (int i=0; i < Nx*Ny; ++i){
            //propose
            int p;
            do{p = choose_p(gen_p);} //bad generator!
            while(p>=Nx*Ny);

            double x = particles[p][0] +
                std::generate_canonical<double,10>(gen_a) *a;
            double y = particles[p][1] +
                std::generate_canonical<double,10>(gen_a) *a;
            //apply periodic boundary conditions
            x = BC(x);
            y = BC(y);

            //check
            if (overlap(x,y,p)){continue;}

            particles[p][0] = x;
            particles[p][1] = y;
        }
    }

    static const int M = 512;
    const double rmax = std::sqrt(2)*L/2;
    const double dA = ( rmax*rmax - d0*d0) * PI/M;

    std::array<unsigned long, M> hist;

    int measurements = 0;

    void measure ()
    /// compute the histogram of particles
    {
        for (int i=0;i < Nx*Ny; ++i){
            double x1 = particles[i][0];
            double y1 = particles[i][1];
            for (int j=i+1; j < Nx*Ny; ++j ){
                double x2 = particles[j][0];
                double y2 = particles[j][1];
                int m = (  pow(distance(x1,y1,x2,y2),2) -
                           d0*d0 ) * PI/dA;
                ++hist[m];
            }
        }
        measurements++;
    }

    std::array<double, M> finalize ()
    {
        std::array<double, M> fin;
        for (int i=0; i < M; ++i){
           fin[i] =  hist[i] / double(measurements);
        }
        return fin;
    }

};

struct Timer{
    std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1;

    void start ()
    {
        t0 = std::chrono::high_resolution_clock::now();
    }
    void end ()
    {
        t1 = std::chrono::high_resolution_clock::now();
    }

    double time () const
    {
        std::chrono::duration<double> dt = t1 - t0;
        return dt.count();
    }
};

int main (int argc, char** argv)
{
    int numThreads = omp_get_max_threads();
    if(argc > 1){
        numThreads = std::stoi(argv[1]);
        omp_set_num_threads(numThreads);
    }
    const int S = 500;
    const int Seq = 100;

    Timer t;
    t.start();
    Problem p;
    auto _ = p.IC();

    for (int i = 0; i < Seq; ++i){
        p.sweep();
    }
    p.measure();
    auto histogram = p.finalize();

    #pragma omp parallel
    {
        Problem p_private(p.particles,313481%(1457+omp_get_thread_num()*31347));


        #pragma omp for nowait
        for (int i = 0; i < S; ++i)
        {
           p_private.sweep();
           p_private.measure();
           if(omp_get_thread_num()==0){
            cout << i << endl;
           }
        }

        #pragma omp critical
        {
            histogram  += p_private.finalize();
        }
    }

    for (auto h : histogram){
        h /= numThreads;
    }

    t.end();
    cout << numThreads << "\t" << t.time() << endl;
    return 0;
}
