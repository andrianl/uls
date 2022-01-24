#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    const byte *s = src;
    byte *d = dst;

    while (n--)
        *d++ = *s++;
    return dst;
}
