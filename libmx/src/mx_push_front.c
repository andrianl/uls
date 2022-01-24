#include "libmx.h"

void mx_push_front(t_list **list, void *data)
{
    t_list *new_head = mx_create_node(data);

    new_head->next = *list;
    *list = new_head;
}
