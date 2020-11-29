/* Programming Techniques for Scientific Simulations, HS 2015
 * Week 12
 */

#ifndef ALGO_DERIVATION
#define ALGO_DERIVATION

enum op {Add, Multiply};

//********


template<class T>
class Constant
{
public:
  Constant(const T v) : _val(v) {}
  T operator()(const T) const { return _val; }
  T derivative(const T) const { return 0;}
  Constant derivative() const { return Constant(_val); }
private:
  T _val;
};

template <class T>
Constant<T> constant(const T x)
{
  return Constant<T>(x);
}

//********

template <class T>
class Variable
{
public:
  T operator()(const T x) const { return x; }
  T derivative(const T x) const { return 1; }
  Constant<T> derivative() const { return constant((T)1.0); }
};

//********

template<class left, class right, op o>
class Expression
{
public:
  Expression(const left _l, const right _r) : l(_l), r(_r) { }

  template <class T>
  T operator()(const T x)
  {
    switch (o)
      {
      case Add:
        return l(x) + r(x);
      case Multiply:
        return l(x) * r(x);
      }
  }

  template <class T>
  T derivative(const T x)
  {
    switch (o)
      {
      case Add:
        return l.derivative(x) + r.derivative(x);
      case Multiply:
        return l.derivative(x)*r(x) + l(x)*r.derivative(x);
      }
  }

  Expression derivative()
  {
      switch (o)
      {
      case Add:
        return l.derivative() + r.derivative();
      case Multiply:
        return l.derivative()*r + l*r.derivative();
      }
  }

private:
  left l;
  right r;
};

//********

template<class L, class R>
Expression<L, R, Multiply> operator*(const L l, const R r)
{
  return Expression<L, R, Multiply>(l, r);
}

template<class L, class R>
Expression<L, R, Add> operator+(const L l, const R r)
{
  return Expression<L, R, Add>(l, r);
}

#endif //ALGO_DERIVATION
