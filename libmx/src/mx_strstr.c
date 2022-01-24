#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle)
{
    register char *a, *b;

    b = (char *)needle;
    if (*b == 0)
    {
        return (char *)haystack;
    }
    for (; *haystack != 0; haystack += 1)
    {
        if (*haystack != *b)
        {
            continue;
        }
        a = (char *)haystack;
        while (1)
        {
            if (*b == 0)
            {
                return (char *)haystack;
            }
            if (*a++ != *b++)
            {
                break;
            }
        }
        b = (char *)needle;
    }
    return NULL;
}
