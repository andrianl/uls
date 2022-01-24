#include "libmx.h"

int mx_tolower(int c)
{
    return mx_isupper(c) ? c + 32 : c;
}
