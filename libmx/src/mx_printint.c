#include "libmx.h"
//#include <limits.h>

void mx_printint(int n)
{

    char integer[12];
    ubyte count = 0;
    if (n <= INT_MIN)
    {
        mx_printstr("-2147483648");
        return;
    }
    if (n >= INT_MAX)
    {
        mx_printstr("2147483647");
        return;
    }

    if (!n)
    {
        mx_printchar('0');
        return;
    }

    if (n < 0)
    {
        n = -n;
        mx_printchar('-');
    }

    while (n)
    {
        integer[count] = n % 10 + '0';
        n = n / 10;
        count++;
    }

    integer[count + 1] = '\0';
    mx_str_reverse(integer);
    mx_printstr(integer);
}
