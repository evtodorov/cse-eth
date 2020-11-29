/*
 * This is the test program for fish class
 */

#include "fish.hpp"
#include <cassert>
#include <iostream>


void test (unsigned bad_threshold, unsigned maturity_age)
{
    Penna::Genome::set_bad_threshold(bad_threshold);
    Penna::Fish::set_maturity_age(maturity_age);
    Penna::Genome genome;
    
    for (std::size_t index=0; index < 1000; ++index)
    {
        genome.mutate();
        Penna::Fish fish(genome);
        
        while (!fish.is_dead()) {
            assert(genome.count_bad(fish.age()) <= bad_threshold);
            
            if (fish.is_pregnant()) {
                Penna::Fish child = fish.give_birth();
                assert(child.age()==0);
                assert(!child.is_pregnant());
            }
            fish.grow();
        }
        assert(fish.age()==Penna::Fish::maximum_age+1 ||
               genome.count_bad(fish.age())==bad_threshold+1);
        
    }
}

int main(int agrc, char** argv)
{
    // normal cases
    test(4,1);
    test(3,4);
    test(2,5);
    // boundary cases
    test(0,5);
    test(4,Penna::Fish::maximum_age);
    test(Penna::Fish::maximum_age,6);
    test(Penna::Fish::maximum_age,Penna::Fish::maximum_age);
    
    std::cout<<"Fish tests passed." << std::endl;
    return 0;
}
