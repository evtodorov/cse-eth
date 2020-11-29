#include "timer.hpp"

void Timer::start(){
    start_ = std::chrono::system_clock::now();
}
void Timer::stop(){
    stop_ = std::chrono::system_clock::now();
}
double Timer::duration(){
    double dt = std::chrono::duration_cast<std::chrono::microseconds>(stop_-start_).count();
    return dt/10e+6;
}
