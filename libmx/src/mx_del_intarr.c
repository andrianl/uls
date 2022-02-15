#include "libmx.h"

void mx_del_intarr(int **arr, int num)
{
    if (!arr)
        return;

    for (size_t i = 0; (int)i < num; i++)
        free(arr[i]);
    free(arr);
}
