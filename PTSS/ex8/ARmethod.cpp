#include <iostream>
#include <random>
#include <cmath>

const double M_E2= std::exp(2.0);
const double M_PI= std::acos(-1.0);

template<class T = double, class P>
class WeirdDistribution{
    typedef T result_type;
    typedef P param_type;
public:
    WeirdDistirbution ()
        : init_state_(1)
    {};
    WeirdDistribution (param_type p)
        : p_(p)
    {};

    void reset () {};

    param_type param () const
    {
        return p_;
    };

    void param ( param_type p)
    {
        p_ = p;
    };

    template<class G>
    param_type operator() (G g, param_type p = p_)
    {
        std::normal_distribution<result_type> N(0,p);
        result_type h,u;
        const double lambda = 1.0/p/std::sqrt(2*M_PI);

        do{
            h = N_(g);
            u = std::generate_canonical<result_type,10>(prn_);
        }
        while ( u > )
    };

private:
    std::mt19937 prn_(38947);
    param_type p_;
};


int main ()
{


    return 0;
}
