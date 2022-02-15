#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len)
{
    byte *dest = dst;
    byte const *source = src;
    if (source < dest)
        /* Moving from low mem to hi mem; start at end.  */
        for (source += len, dest += len; len; --len)
            *--dest = *--source;
    else if (source != dest)
    {
        /* Moving from hi mem to low mem; start at beginning.  */
        //for (; len; --len)
        while (len--)
            *dest++ = *source++;
    }
    return dst;
}
