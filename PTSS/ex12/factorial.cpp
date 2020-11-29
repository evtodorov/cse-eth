#include <iostream>

typedef unsigned long long uint_type;

template<uint_type N>
struct factorial{
    static uint_type eval()
    {
        return N*factorial<N-1>::eval();
    }
};

template<>
struct factorial<1>{
    static uint_type eval()
    {
        return 1;
    }
};

template<uint_type N, uint_type K, bool are_equal>
struct factorial_ratio{
    static uint_type eval()
    {
        return N*factorial_ratio<N-1,K,N==K+1>::eval();
    }
};

template<uint_type N, uint_type K>
struct factorial_ratio<N,K,true>{
    static uint_type eval()
    {
        return 1;
    }
};

template<uint_type N, uint_type K>
struct binomial_coefficient{
    static uint_type eval()
    {
        return factorial_ratio<N,K,false>::eval()/factorial<N-K>::eval();
    }
};


int main()
{
    const uint_type n = 25;
    const uint_type k = 10;

    std::cout << factorial<n>::eval() << std::endl;

    std::cout << binomial_coefficient<n,k>::eval() << std::endl;

    return 0;
}
