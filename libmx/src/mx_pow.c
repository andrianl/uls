#include "libmx.h"

double mx_pow(double n, unsigned int pow)
{
    double result = 1;

    for (unsigned int i = 0; i < pow; i++)
    {
        result *= n;
    }

    return result;
}

float mx_powf(float base, int exp)
{

    if (exp == 0)
        return 1;
    float temp = mx_powf(base, exp / 2);
    if (exp % 2 == 0)
        return temp * temp;
    else
    {
        if (exp > 0)
            return base * temp * temp;
        else
            return (temp * temp) / base; //negative exponent computation
    }
}
