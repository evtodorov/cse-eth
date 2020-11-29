#include "random.hpp"
#include <iostream>


Generator::N Generator::generate(){
    Xn_ = (a_*Xn_+c_)&m_; ///about 50% faster than %
    return Xn_;
}
Generator::N Generator::max()const{
    return max_;
} ;

