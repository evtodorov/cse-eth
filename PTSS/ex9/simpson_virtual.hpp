#ifndef SIMPSON_VIRT
#define SIMPSON_VIRT

struct Base{
    base ();
    virtual double operator() (double) const = 0;
};


double integrate_virtual (double a, double b, unsigned N, Base& f)
{
    double out = 0;
    double x = a;
    double dx = (b - a) / N;

    for (unsigned i = 0; i < N; ++i)
    {
        double temp = f(x);
        x += dx / 2;
        temp += 4*f(x);
        x += dx / 2;
        temp += f(x);
        out +=  dx / 6 * temp;
    }

    return out;
}

#endif //SIMPSON_VIRT
