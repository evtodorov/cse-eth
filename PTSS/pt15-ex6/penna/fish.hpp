#ifndef FISH_HPP
#define FISH_HPP

#include "genome.hpp"

namespace Penna
{

/**
 * Fish having a genome and age.
 */
class Fish
{
public:
    static const age_type maximum_age = Genome::number_of_genes;

    static void set_maturity_age( age_type );

    /// Default constructor: Uses all good genome.
    Fish();
    /// Constructor using a given genome.
    Fish( const Genome& gen );

    bool is_dead() const;
    bool is_pregnant() const;
    age_type age() const;

    /// Make the animal grow older by one year.
    void grow();
    /// Create a baby fish inheriting its genome from this except for some random mutations.
    Fish give_birth() const;

private:
    /// Maturity age. Parameter R in Penna's paper.
    static age_type maturity_age_;

    const Genome gen_;
    age_type age_;
};

} // end namespace Penna

#endif // !defined FISH_HPP
