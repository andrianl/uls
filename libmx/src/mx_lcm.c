#include "libmx.h"
//#include <limits.h>

int mx_lcm(int a, int b)
{
    if (a == 0 && b == 0)
        return 0;

    int an = (a < 0 && a != INT_MIN) ? a * -1 : a;
    int bn = (b < 0 && b != INT_MIN) ? b * -1 : b;

    return an * bn / mx_gcd(an, bn);
}
