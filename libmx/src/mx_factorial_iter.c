#include "libmx.h"
//#include <limits.h>

int mx_factorial_iter(int n)
{
    unsigned result = 1;

    for (unsigned i = 1; i < (unsigned)n + 1; i++)
    {
        result *= i;

        if (result > INT_MAX)
        {
            return 0;
        }
    }

    return (int)result;
}
