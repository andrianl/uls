#include <libmx.h>

int mx_count_substr(const char *str, const char *sub)
{
    if (!str || !sub)
        return -1;

    if (mx_strcmp(sub, "") == 0)
        return 0;

    unsigned string_length = mx_strlen(str);
    unsigned sub_length = mx_strlen(sub);

    if (string_length >= sub_length)
    {
        unsigned result = 0;
        for (bool is_sub; (str = mx_strchr(str, *sub)); str += is_sub ? 1 : sub_length)
            if ((is_sub = mx_strncmp(str, sub, sub_length)) == 0)
                ++result;

        return (int)result;
    }
    return str && sub ? 0 : -1;
}
