#include "libmx.h"

int mx_toupper(int c)
{
    return mx_islower(c) ? c - 32 : c;
}
