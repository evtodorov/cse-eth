#include "genome.hpp"
#include <random>

namespace Penna{

age_type Genome::mutation_rate_ = 2;
age_type Genome::bad_threshold_ = 2;

void Genome::set_mutation_rate ( age_type r)
{
    mutation_rate_ = r;
}

void Genome::set_bad_threshold ( age_type t)
{
    bad_threshold_ = t;
}

age_type Genome::count_bad ( age_type age ) const
{
   return (genes_<<(number_of_genes-age-1)).count();
}

age_type Genome::get_bad_threshold ( ) const
{
    return bad_threshold_;
}

std::mt19937 prn(438765);

void Genome::mutate ( )
{
    std::uniform_int_distribution<age_type> rand_gene(0,Genome::number_of_genes-1);

    for (age_type i=0; i < mutation_rate_; ++i){
        genes_.flip( rand_gene(prn) );
    }
}
}
