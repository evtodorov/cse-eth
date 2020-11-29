#include <iostream>
#include <array>
#include <random>
#include <cmath>
#include <cstddef>
#include <utility>
#include <chrono>
using std::cout; using std::endl;


double PI = std::acos(-1);

template<size_t N, class T>
std::ostream& operator<<(std::ostream& os, const std::array<T,N> arr)
{

  for (auto a : arr){
    os << a << "\n";
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

std::mt19937 gen_p (34534542);
std::mt19937 gen_a (52348734);

struct Problem{
    static const int Nx = 14;
    static const int Ny = 16;
    const double L = 1.0;
    const double d0 = 0.875 * L / Nx;
    const double a = (L/Nx) - d0;

    typedef typename std::array<double, 2> Particle;
    typedef typename std::array<Particle, Nx*Ny> Particles;

    Particles particles;

    void init ()
    ///initial conditions, honeycomb
    {
        hist.fill(0);
        double dx = L/Nx;
        double dy = std::sqrt(3.)/2. * dx;
        for (int i = 0; i < Nx; ++i){
            for (int j = 0; j < Ny; ++j){

                particles[i*Ny+j][0] = (i+0.25+(j%2)/2.)*dx;
                particles[i*Ny+j][1] = (j+0.5)*dy;
            }
        }
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
//cout << m << endl;
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

int main ()
{
    const int S = 64;
    const int Seq = 64;
    Timer t;
    t.start();
    Problem p;
    p.init();
    //cout << p.particles << endl;
    for (int i = 0; i < Seq; ++i){
        p.sweep();
    }
    //cout << p.particles << endl;
    for (int i = 0; i < S; ++i){
        p.sweep();
        p.measure();
    }
    t.end();
    //cout << p.particles << endl;


    auto histogram = p.finalize();
    //cout << "Time: " << t.time();
    std::cout << histogram << endl;

    return 0;
}
