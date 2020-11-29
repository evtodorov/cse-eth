#include <timer.hpp>
#include <random.hpp>

#include <iostream>

int main() {
    
    const size_t N = 1000000000;
    
    Timer t;
    Generator R(42);
    double s(0.0);
    
    t.start();
    for (size_t n=0; n<N; ++n)
        s += static_cast<double>( R.generate() ) / R.max();
    t.stop();
    
    s /= N;
    
    std::cout << "Mean of the random number engine is: " << s << "." << std::endl;
    std::cout << "Computed in " << t.duration() << " seconds." << std::endl;
}
