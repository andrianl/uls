#include "libmx.h"

int mx_bubble_sort(int *arr, int size)
{
    unsigned swaps = 0;
    for (unsigned i = 0; i < (unsigned)size - 1; i++)

        for (unsigned j = 0; j < (unsigned)size - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swaps++;
            }
    return (int)swaps;
}
