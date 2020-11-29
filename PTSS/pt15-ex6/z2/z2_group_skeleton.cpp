#include <iostream>

enum Z2 { Plus, Minus };


template<class T>
T identity_element()
{
    return T(1);
}


template <>
Z2 identity_element<Z2>()
{
    return Plus;
}



Z2 operator*(const Z2 a, const Z2 b)
{
  if (a==b){
    return Plus;
  }
  else{
    return Minus;
  }
}

std::ostream& operator<<(std::ostream& os, const Z2 a)
{

  if (a==Plus){
    os << "+";
  }
  else if (a==Minus){
    os << "-";
  }

  return os;
}

template<class T>
T operator*(const T a, const Z2 b)
{
  if (b==Minus){
    return -1*a;
  }
  else{
    return a;
  }
}

template<class T>
T operator*(const Z2 b, const T a)
{
  return a*b;
}

template<class T>
T mypow(T a, const unsigned int n)
{
  T b = identity_element<T>();
  for(unsigned int i=n; i>0; --i){
    b = b*a;
  }
  return b;
}

int main()
{
  // some testing: feel free to add your own!
  std::cout << Plus << std::endl;
  std::cout << Plus*Minus << std::endl;
  std::cout << Plus*-5*Plus << std::endl;
  Z2 c = identity_element<Z2>();
  std::cout << (1.+3.)*mypow(-1,27) << std::endl;
  std::cout << (1.+3.)*mypow(Minus,4) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "Plus^" << i << " = " << mypow(Plus,i) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "Minus^" << i << " = " << mypow(Minus,i) << std::endl;
  for (unsigned i=0; i<7; i++)
    std::cout << "2^" << i << " = " << mypow(2.0,i) << std::endl;
  return 0;
}
