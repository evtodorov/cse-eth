#ifndef simpson_hpp
#define simpson_hpp
//case F is a function object
template < class F>
struct domain_type{
    typedef typename F::argument_type type;
};
template < class F >
struct result_type{
    typedef typename F::result_type type;
};

//case F is a function pointer
template <class R, class T>
struct domain_type<R(*)(T)>{
    typedef T type;
};
template <class R,class T>
struct result_type<R(*)(T)>{
    typedef R type;
};



template<class F>
typename result_type<F>::type integrate_template (
                        typename domain_type<F>::type a,
                        typename domain_type<F>::type b,
                                         unsigned int N,
                                                    F f)
{
    typedef typename result_type<F>::type r_type;
    typedef typename domain_type<F>::type d_type;
    r_type out = 0;
    d_type x = a;
    d_type dx = (b - a) / N;

    for (unsigned int i = 0; i < N; ++i)
    {
        r_type temp = f(x);
        x += dx / 2;
        temp += 4*f(x);
        x += dx / 2;
        temp += f(x);
        out +=  dx / 6 * temp;
    }

    return out;
}
#endif // simpson_hpp

