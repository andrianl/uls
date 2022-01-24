#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count)
{
    unsigned start = 0;
    unsigned end = size - 1;
    unsigned mid = (start + end) / 2;

    while (start <= end)
    {
        (*count)++;

        if (mx_strcmp(arr[mid], s) == 0)
            return mid;

        else if (mx_strcmp(arr[mid], s) < 0)
            start = mid + 1;

        else
            end = mid - 1;
        mid = (start + end) / 2;
    }
    *count = 0;
    return -1;
}
