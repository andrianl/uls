#include "libmx.h"

int mx_list_size(t_list *list)
{
    ubyte result = 0;

    while (list != NULL)
    {
        result++;
        list = list->next;
    }

    return (int)result;
}
