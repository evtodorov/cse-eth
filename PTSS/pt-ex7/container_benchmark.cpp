#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <cstddef>
#include <random>
#include <cassert>

const size_t k    = 1000000;

struct Timer{
    std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1;
    typedef double value_type;
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
        std::chrono::duration<value_type> dt = t1 - t0;
        return dt.count();
    }
};

template<class T>
typename Timer::value_type time ( T& container)
{
    ///quite useless to advance the iterator of a set YOU RETARD
    size_t n = container.size();

    std::mt19937 rnd(284322);
    std::uniform_int_distribution<> uid(0, n-1);
    Timer t;

    t.start();
    for (size_t i=0; i < k; ++i){
        size_t loc = uid(rnd);
        auto iter = container.begin();
        std::advance(iter, loc+1);
        iter = container.insert(iter, 2*loc+1);
        if (container.size() == n){
            continue;
        }
        container.erase(iter);

    }
    t.end();

    return t.time();
}

int main(int argc, char** argv)
{
    if ( argc <= 1){
        std::cout << ">> container_benchmark CONTAINER_SIZE \n";
        return 0;
    }

    const size_t size = std::stoi(argv[1]);

    typedef long value_type;

    value_type array[size];
    std::vector<value_type> vector;
    vector.resize(size);

    for (size_t i=0; i < size; ++i){
        array[i] = 2*i;
        vector[i] = array[i];
    }
    std::list<value_type> list(vector.begin(),vector.end());
    std::set<value_type> set(vector.begin(),vector.end());

    Timer::value_type t_vector, t_list, t_set;
    std::cout << "start timing vector\n";
    t_vector = time(vector);
    assert(vector.size()==size);
     std::cout << "start timing list\n";
    t_list = time(list);
    assert(list.size()==size);
     std::cout << "start timing set\n";
    t_set = time(set);
    assert(set.size()==size);

    std::cout << t_vector << "\t" << t_list << "\t" << t_set << std::endl;
    return 0;
}
