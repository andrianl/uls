#include "libmx.h"
//#include <limits.h>

int mx_gcd(int a, int b)
{
    int an = (a < 0 && a != INT_MIN) ? a * -1 : a;
    int bn = (b < 0 && b != INT_MIN) ? b * -1 : b;

    if (bn != 0)
        return mx_gcd(bn, an % bn);
    return an;
}
