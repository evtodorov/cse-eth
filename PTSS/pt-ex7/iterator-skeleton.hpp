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

  FwdIterator(){};
  /* You may need an additional constructor */

  reference operator* () const;
  FwdIterator<value_type>& operator++ ();

  bool operator== ( const FwdIterator<value_type>& ) const;
  bool operator!= ( const FwdIterator<value_type>& ) const;
  value_type* operator-> () const;
  FwdIterator<value_type> operator++(int);

  /* add Bidirectional iterator support */

private:
  // ...
};

#endif 
