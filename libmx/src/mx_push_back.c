#include "libmx.h"

void mx_push_back(t_list **list, void *data)
{
    t_list *new_tail = mx_create_node(data);
    t_list *temp = *list;

    if (*list == NULL)
    {
        *list = new_tail;
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_tail;
}
