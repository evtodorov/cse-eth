// copyright by me
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <utility> // for std::swap
#include <cassert>

#include "iterator.hpp"

template <class T>
class Array
{
public:
  typedef std::size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef FwdIterator<T> iterator;
  Array(); // empty array
  Array(size_type, value_type = value_type() ); // Array of given size
  Array(const Array<T>&); // copy of an Array
  ~Array();

  Array<T>& operator= (Array<T>); // assign another array

  size_type size() const;  // the size of the array
  void resize(size_type); // change the size of the array

  reference operator[](size_type index); // a[i]=5.;
  const_reference operator[](size_type index) const; // X=a[i];

  void swap(Array<T>& x);

  // might want to add: void sort();

  iterator begin() const
  {
      return FwdIterator<T>(v_);
  }
  iterator end()   const
  {
      return FwdIterator<T>(v_+sz_);
  }

private:
  size_type sz_; // size
  value_type* v_;   // pointer to the actual array
};


template <class T>
Array<T>::Array()
 : sz_(0)
 , v_(0)
{
}


template <class T>
Array<T>::Array(size_type s,value_type initial)
 : sz_(s)
 , v_(new value_type[sz_])
{
  for (size_type i = 0; i<sz_; ++i)
    v_[i] = initial;
}


template <class T>
Array<T>::Array(const Array<T>& rhs)
 : sz_(rhs.sz_)
 , v_(new value_type[sz_])
{
  for (size_type i = 0;i<sz_;i++)
    v_[i] = rhs.v_[i];
}


template <class T>
Array<T>::~Array()
{
  delete[] v_;
}


template <class T>
void Array<T>::swap(Array<T>& rhs)
{
  std::swap(sz_,rhs.sz_);
  std::swap(v_,rhs.v_);
}



// and the best version: pass by value so that a copy is already created
template <class T>
Array<T>& Array<T>::operator = (Array<T> rhs)
{
  swap(rhs);
  return *this;
}


template <class T>
typename Array<T>::size_type Array<T>::size() const  // the size of the array
{
  return sz_;
}


// elegant implementation using swap
template <class T>
void Array<T>::resize(size_type s)
{
  Array<T> w(s);
  for(int i = 0; i<sz_ && i<s; i++)
    w.v_[i] = v_[i];
  swap(w);
}


template <class T>
typename Array<T>::reference Array<T>::operator[](size_type index)
{
  assert (index>=0 && index < size());
  return v_[index];
}


template <class T>
typename Array<T>::const_reference Array<T>::operator[](size_type index) const
{
  assert (index>=0 && index < size());
  return v_[index];
}

#endif
