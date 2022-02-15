#include "libmx.h"

char *mx_strndup(const char *s1, size_t n)
{
    unsigned slen = (unsigned)mx_strlen(s1);
    unsigned len = slen < n ? slen : n;
    char *copy = malloc(len + 1);
    mx_memcpy(copy, s1, len);
    copy[len] = '\0';
    return copy;
}
