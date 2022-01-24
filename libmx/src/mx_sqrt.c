#include "libmx.h"

int mx_sqrt(int x)
{
    unsigned long long result = 0;

    if (x < 2)
        return result += (x == 1);

    unsigned long long start = 1;
    unsigned long long end = x / 2;
    while (start <= end)
    {
        unsigned long long mid = (start + end) / 2;
        unsigned long long sqr = mid * mid;
        if (sqr == (unsigned long long)x)
        {
            return (int)mid;
        }
        else if (sqr < (unsigned long long)x)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }
    return (int)result;
}
