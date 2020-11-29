#ifndef ITERATOR_HPP_
#define ITERATOR_HPP_
#include <cassert>

/* Bidirectional Iterator Requirements:

Iterator:
- CopyConstructible.
- CopyAssignable.
- Destructible.
- Supports: *a. (Dereferenceable)
- Supports: ++a. (Preincrementable)

Input Iterator:
- All requirements of an iterator.
- Supports: ==. (EqualityComparable)
- Supports: !=.
- Supports: ->.
- Supports: a++. (Postincrementable)

Forward Iterator:
- All requirements of an input iterator.
- DefaultConstructible.
- Supports expression: *a++.

Bidirectional Iterator:
- All requirements of a forward iterator.
- Predecrementable.
- Postdecrementable.
- Supports expression: *a--.

*/

template<typename T>
class FwdIterator
{
public:
    typedef T value_type;
    typedef T& reference;

    FwdIterator() {};
    FwdIterator( const FwdIterator<value_type>& ); //CopyConstructible
    FwdIterator( value_type * ); //used to define begin & end
    /* You may need an additional constructor */

    reference operator* () const;
    FwdIterator<value_type>& operator++ ();

    bool operator== ( const FwdIterator<value_type>& ) const;
    bool operator!= ( const FwdIterator<value_type>& ) const;
    value_type* operator-> () const;
    FwdIterator<value_type> operator++(int);

    /* add Bidirectional iterator support */

private:
    value_type* address_;
};

//checked iterator -> should know when you are out of bounds
template<typename T>
FwdIterator<T>::FwdIterator(value_type* pointer)
{
    address_ = pointer;
}
template<typename T>
typename FwdIterator<T>::reference FwdIterator<T>::operator* () const
{
    return *address_;
}
template<typename T>
FwdIterator<T>& FwdIterator<T>::operator++ ()
{
    return *address_ + 1;
}
template<typename T>
bool FwdIterator<T>::operator== (const FwdIterator<T>& rhs) const
{
    return (rhs.address_ == address_);
}
template<typename T>
bool FwdIterator<T>::operator!= (const FwdIterator<T>& rhs) const
{
    return (rhs.address_ != address_);
}
template<typename T>
T* FwdIterator<T>::operator-> () const
{
    return address_;
}
template<typename T>
FwdIterator<T> FwdIterator<T>::operator++ (int)
{

}

#endif
