#include "libmx.h"

void mx_print_arr_int(const int *arr, int size)
{
    for (unsigned i = 0; i < (unsigned)size; i++)
    {
        mx_printint(arr[i]);
        mx_printchar(' ');
    }
}
