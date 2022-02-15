#include "libmx.h"

static void swap_q(int *x, int *y, unsigned *count)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
	++(*count);
}

int mx_quicksort(int *arr, int left, int right)
{
	if (!arr)
		return -1;

	unsigned swaps = 0, i = left, j = right - 1, pivot = arr[right];

	while (i < j)
	{
		while (arr[i] <= (int)pivot && (int)i < right)
		{
			i++;
		}

		while (arr[j] > (int)pivot)
		{
			--j;
		}

		if (i > j)
			break;

		swap_q(&arr[i++], &arr[j--], &swaps);
	}

	if (arr[i] > (int)pivot)
		swap_q(&arr[i], &arr[right], &swaps);
	if ((int)j > left)
		swaps += mx_quicksort(arr, left, j);
	if ((int)i + 1 < right)
		swaps += mx_quicksort(arr, i + 1, right);

	return (int)swaps;
}
