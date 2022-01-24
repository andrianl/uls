#include "libmx.h"

int mx_max(int a, int b)
{
    int diff = a - b;
    int dsgn = diff >> 31;
    return a - (diff & dsgn);
}

int mx_min(int a, int b)
{
    int diff = a - b;
    int dsgn = diff >> 31;
    return b + (diff & dsgn);
}
