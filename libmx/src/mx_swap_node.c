#include "libmx.h"

void mx_swap_node(void **s1, void **s2)
{
    void *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}
