#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2)
{

    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 == 0)
        return mx_strdup(s2);
    if (s2 == 0)
        return mx_strdup(s1);

    char *new_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));

    new_str = mx_strcat(new_str, s1);
    new_str = mx_strcat(new_str, s2);

    return new_str;
}
