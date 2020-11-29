#include "testerClass.h"

testerClass::testerClass()
{
    //ctor
}

testerClass::~testerClass()
{
    //dtor
}

testerClass::testerClass(const testerClass& other)
{
    //copy ctor
}

testerClass& testerClass::operator=(const testerClass& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
