#include "libmx.h"

void *mx_realloc(void *ptr, size_t size)
{

    if (!ptr)
    {
        return malloc(size);
    }

    unsigned current_size = mx_malloc_size(ptr);

    if (size <= current_size)
    {
        return ptr;
    }

    void *new_ptr = malloc(size);
    mx_memmove(ptr, new_ptr, current_size);
    free(ptr);
    return new_ptr;
}
