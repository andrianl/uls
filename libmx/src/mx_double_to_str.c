#include "libmx.h"

char *mx_double_to_str(double n)
{
    char *str = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    int temp = (n - (int)n) * 100;
    int i = mx_pow(10, mx_intlen((int)n));
    n += temp % 10 > 4 ? .1 : 0;
    n += i > 10 && temp % 100 > 50 ? 1 : 0;
    str1 = mx_itoa((int)n % i);
    if (i < 100)
    {
        str3 = mx_itoa((int)((n - (int)n) * 10));
        str2 = mx_strjoin(".", str3);
        str = mx_strjoin(str1, str2);
        mx_strdel(&str1);
        mx_strdel(&str2);
        mx_strdel(&str3);
        return str;
    }
    else
    {
        return str1;
    }
}
