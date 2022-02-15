#include "libmx.h"
//#include <limits.h>

#define BASE 10

int mx_atoi(const char *str)
{
    unsigned long long n = 0;
    int i = 0;
    int ch = 1;

    while (mx_isspace(str[i++]))
    {
    }

    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            ch = -1;
        i++;
    }

    while (mx_isdigit(str[i++]))
    {
        if (ch == -1 &&
            ((n > -(LONG_MIN / BASE)) ||
             ((n == -(LONG_MIN / BASE)) && (str[i] - 48 > -(LONG_MIN % BASE)))))
            return 0;
        if ((n > (LONG_MAX / BASE)) ||
            ((n == (LONG_MAX / BASE)) && str[i] - 48 > LONG_MAX % BASE && ch != -1))
            return -1;
        n = n * BASE + str[i] - 48;
    }
    return ch * n;
}
