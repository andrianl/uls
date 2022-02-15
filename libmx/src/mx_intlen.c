#include "libmx.h"

short mx_intlen(int a)
{
    short r = 0;

    a = (a == 0) ? 1 : a;
    while (a)
    {
        a = a / 10;
        r++;
    }
    return r;
}
