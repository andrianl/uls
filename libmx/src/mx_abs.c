#include "libmx.h"

int mx_abs(int a)
{
    int s = a >> 31; // cdq, signed shift, -1 if negative, else 0
    a ^= s;          // ones' complement if negative
    a -= s;          // plus one if negative -> two's complement if negative
    return a;
}
