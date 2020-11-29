#include "genome.hpp"

using namespace Penna;

static void Genome::set_mutation_rate ( age_type new)
{
    mutation_rate_ = new;
}

static void Genome::set_bad_threshold ( age_type new)
{
    bad-threshold_ = new;
}

age_type Genome::count_bad ( age_type age )
{
    age_type bad = 0;
    for (age_type i; i < age; ++i){
        bad += genes_[i];
    }
    return bad;
}

age_type Genome::get_bad_threshold ( )
{
    return bad_threshold;
}

void Genome::mutate ( )
{
    //TODO: mutate
}
