#include "fish.hpp"
#include "genome.hpp"
#include <cassert>
#include <iostream>

namespace Penna{

age_type Fish::maturity_age_ = 0;

Fish::Fish ()
: age_(0),
  gen_(Genome())
{};

Fish::Fish ( const Genome& gen)
: age_(0),
  gen_(gen)
{};

void Fish::set_maturity_age( age_type a )
{
    maturity_age_ = a;
}

bool Fish::is_dead( ) const
{
    return (    (maximum_age < age_)
             || (gen_.get_bad_threshold() < gen_.count_bad(age_))   );
}

bool Fish::is_pregnant () const
{
    return (maturity_age_ < age_);
}

age_type Fish::age() const
{
    return age_;
}

void Fish::grow()
{
    if (!is_dead())
        ++age_;
}

Fish Fish::give_birth() const
{
    if ( is_pregnant() ){
        Genome baby_gen = gen_;
        baby_gen.mutate();
        return Fish( baby_gen );
    }
}

}

