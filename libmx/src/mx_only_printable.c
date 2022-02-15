#include "libmx.h"

void mx_only_printable(void)
{
    for (char target = 126; target < 127 && target > 31; target--)
    {
        mx_printchar(target);
    }
    mx_printchar('\n');
}
