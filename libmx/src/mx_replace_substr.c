#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub,
                        const char *replace)
{
    char *result;  // the return string
    char *ins;     // the next insert point
    char *tmp;     // varies
    int len_rep;   // length of rep (the string to remove)
    int len_with;  // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;     // number of replacements

    // sanity checks and initialization
    if (!str || !sub || !replace)
        return NULL;
    len_rep = mx_strlen(sub);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    // if (!replace)
    //     replace = "";
    len_with = mx_strlen(replace);

    // count the number of replacements needed
    ins = (char *)str;
    for (count = 0; (tmp = mx_strstr(ins, sub)); ++count)
    {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(mx_strlen(str) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--)
    {
        ins = mx_strstr(str, sub);
        len_front = ins - str;
        tmp = mx_strncpy(tmp, str, len_front) + len_front;
        tmp = mx_strcpy(tmp, replace) + len_with;
        str += len_front + len_rep;
    }
    mx_strcpy(tmp, str);
    return result;
}
