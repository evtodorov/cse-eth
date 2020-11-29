#ifndef SIMPSON_INTEGRAL
#define SIMPSON_INTEGRAL

//SYNOPSIS
//	-> integrates a given function represented by a function pointer from a to b using 
//	   the simpson integration rule dividing the interval into given number of bins.
//	   returns a double representing the value of the integral
//PRECONDITIONS
//	-> a < b (makes sense), bins > 0
//POSTCONDITIONS
//	-> none
//DEPENDENCIES
//	-> none
double simpson_integral(double (*f)(double x),
                        double a, double b,
                        int bins);

#endif // SIMPSON_INTEGRAL
