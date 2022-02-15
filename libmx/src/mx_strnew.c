#include "libmx.h"

char *mx_strnew(const int size)
{

    if (size >= 0)
    {
        char *new_string = malloc(size + 1);
        mx_memset(new_string, '\0', size+1);
        return new_string;
    }
    return NULL;
}
