#ifndef RANDOM_H
#define RANDOM_H

#include <cmath>

class Generator{
public:
    typedef unsigned long int N;
private:
    const int seed_;
    const N m_ = pow(2,32);
    const N a_ = 1664525;
    const N c_ = 1013904223;
    const N max_ = m_ - 1;
    N Xn_;
public:
    Generator(N seed = 0)
        : seed_(seed), Xn_(seed)
    {};
    ~Generator(){};
    N max() const;
    N generate();

};
#endif // RANDOM_H
