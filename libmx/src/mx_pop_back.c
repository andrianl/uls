#include "libmx.h"

void mx_pop_back(t_list **list)
{

    if (list == NULL || *list == NULL)
        return;

    t_list *temp = *list;
    //temp = *list;

    if (temp->next == NULL)
    {
        free(*list);
        *list = NULL;
        return;
    }
    else
    {
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    }
}
