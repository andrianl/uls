#include "libmx.h"

void printArray(int *arr)
{
    int i;
    int size = sizeof(*arr)/sizeof(int);
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
