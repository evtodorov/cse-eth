#ifndef PENNA_HPP
#define PENNA_HPP

#include <cstdlib>  //size_t
#include <bitset>   //bitset
#include <vector>   //vector

#define MAXLIFE 32 //compile time bitarray size

typedef unsigned char value_type; // change if MAXLIFE > 255
typedef const size_t size_type;
typedef std::bitset<MAXLIFE> storage_type;
typedef bool gene_type;

class Genome
{
private:
    size_type genome_size_ = MAXLIFE;
    storage_type genes_;
    value_type max_bad_genes_;
    value_type mutation_rate_;
public:
    Genome ()
        :
    {};
    Genome(Genome const&)
        :
    {};
    void mutate (size_type, gene_type);
    void mutation_rate (value_type);    //setter
    value_type mutation_rate () const;  //getter
    void max_bad_genes (value_type);    //setter
    value_type max_bad_genes() const;   //getter
    value_type active_bad_genes(value_type);
};

class Fish
{
private:
    Genome genome_;
    value_type age_;
    value_type reproduction_age_;
public:
    Fish()
        :
    {};
    Fish( Fish const&)
        :
    {};
    void reproduction_age(value_type);  //setter
    value_type reproduction_age() const;//getter
    bool is_dead() {} const;
    bool is_pregnant() {} const;
    void grow () {}; //get older
    Fish give_birth () {} const;
};

class Population
{
private:
    size_type N_max_;
    std::vector<Fish> fishes_;
    size_type N_current_;
public:
    Population (size_type N)
        :
    {};
    void add (Fish&) {};
    void remove (Fish&) {};
    size_type N_current () {} const;
    void sweep () {};
};


#endif // PENNA_HPP
