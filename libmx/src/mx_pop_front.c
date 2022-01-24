#include "libmx.h"

void mx_pop_front(t_list **list)
{
    if (list == NULL || *list == NULL)
        return;

    t_list *temp = *list;
    *list = temp->next;
    free(temp);
    temp = NULL;
}
