#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer{
typedef std::chrono::system_clock::time_point s;
public:
    Timer(){};
    ~Timer(){};
    void start();
    void stop();
    double duration();
private:
    s start_;
    s stop_;
};
#endif // TIMER_H
