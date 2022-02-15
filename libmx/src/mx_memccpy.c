#include "libmx.h"

void *mx_memccpy(void *dst, const void *src, int c, size_t n)
{
    byte t;
    byte *dest = (char *)dst;
    const byte *source = (const char *)src;

    for (unsigned i = 0; i < n; i++)
    {
        dest[i] = t = source[i];
        if (t == '\0')
            break;
        if (t == c)
            return &dest[i + 1];
    }
    return NULL;
}
