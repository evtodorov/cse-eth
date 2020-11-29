#include "simpson_integral.hpp"

double simpson_integral(double (*function) (double), double a, double b, int bins)
{

	double increment = (b - a) / bins;
	double sum = 0;

	for(int i = 0; i < bins; i++)
	{
		sum += (function(a + i*increment) + 4 * function(a + i*increment + increment/2) + function(a + i*increment + increment));
	}

	sum = sum * increment/6;

	return sum;

}