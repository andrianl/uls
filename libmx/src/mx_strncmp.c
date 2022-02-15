#include "libmx.h"

int mx_strncmp(register const char *s1, register const char *s2, register size_t n)
{

    if (n == 0)
        return (0);
    while (n--)
    {
        if (*s1 != *s2++)
            return (*(unsigned char *)s1 - *(unsigned char *)--s2);
        if (*s1++ == 0)
            break;
    }
    return (0);
}
