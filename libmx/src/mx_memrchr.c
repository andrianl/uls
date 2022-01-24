#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
    byte *ptr = (byte *)s;

    while (n--)
    {
        if (*(ptr + n) == c)
            return ptr + n;
    }
    return NULL;
}
