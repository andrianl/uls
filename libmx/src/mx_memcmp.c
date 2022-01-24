#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n)
{
    if (n != 0)
    {
        const ubyte *p1 = s1, *p2 = s2;
        while (n-- != 0)
        {
            if (*p1++ != *p2++)
                return (*--p1 - *--p2);
        }
    }
    return 0;
}
