#include "libmx.h"

int mx_count_words(const char *str, char c)
{
    if (!str)
        return -1;

    unsigned words = 0;

    while (*str)
    {

        while (*str && *str == c)
        {
            ++str;
        }

        if (*str && *str != c)
        {
            while (*str && *str != c)
            {
                ++str;
            }
            ++words;
        }
    }
    return (int)words;
}
