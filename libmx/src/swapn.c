#include "libmx.h"

void swapn(void *v1, void *v2, int size)
{

	char buffer[size];

	mx_memcpy(buffer, v1, size);
	mx_memcpy(v1, v2, size);
	mx_memcpy(v2, buffer, size);
}
