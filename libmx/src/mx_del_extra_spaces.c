#include "libmx.h"

char *mx_del_extra_spaces(const char *str)
{
    if (str)
    {

        char *trim = mx_strtrim(str);
        ubyte x = 0;

        for (ubyte i = 0; trim[i]; ++i)
        {
            if (!mx_isspace(trim[i]) )
            {
                trim[x++] = trim[i];
            }

            if ((mx_isspace(trim[i]) && !mx_isspace(trim[i - 1])))
            {
                trim[x++] = ' ';
            }
        }

        trim[x] = '\0';
        return trim;
    }
    return NULL;
}



