#include "fish.hpp"

using namespace Penna;

Fish::Fish ()
: age_(0),
  gen_(Genome())
{};

Fish::Fish ( const Genome& gen)
: age_(0),
  gen_(gen)
{};

void Fish::set_maturity_age( age_type new )
{
    maturity_age_ = new;
}

bool Fish::is_dead( )
{
    //TODO: isdead
}

bool Fish::is_pregnant ()
{
    //TODO: ispregnant
}

age_type Fish::age()
{
    return age_;
}

void Fish::grow()
{
    ++age_;
}

Fish give_birth()
{
    Fish baby = Fish(const Genome gen_);
    baby.gen_.mutate();
}
