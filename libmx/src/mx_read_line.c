#include "libmx.h"
//#include <unistd.h>

static t_fd *mx_fill_lst(int fd)
{
    t_fd *lst;

    lst = (t_fd *)malloc(sizeof(t_fd));
    lst->fd = fd;
    lst->eof = false;
    lst->next = NULL;
    lst->str = 0;

    return lst;
}

static bool strchr_cut(char **tmp1, char **s, char del)
{
    char *tmp2;

    *tmp1 = 0;
    for (int i = 0; (*s)[i]; ++i)
    {
        if ((*s)[i] == del)
        {
            *tmp1 = mx_strndup(*s, i);
            tmp2 = mx_strndup(*s + i + 1, mx_strlen(*s) - i - 1);
            free(*s);
            *s = tmp2;
            return false;
        }
    }
    if (!*tmp1)
    {
        *tmp1 = *s;
        *s = 0;
    }
    return true;
}

static bool strchr_join(char **d, char **s, char del)
{
    bool contin;
    char *tmp;
    char *tmp2;

    if (!*s)
        *s = mx_strnew(0);
    contin = strchr_cut(&tmp, s, del);
    if (!*d)
        *d = tmp;
    else
    {
        tmp2 = mx_strjoin(*d, tmp);
        free(*d);
        free(tmp);
        *d = tmp2;
    }
    return contin;
}

static int mx_read(char **s, t_fd *lst, size_t size, char del)
{
    int rd;
    char buf[size + 1];

    if (lst->eof && !lst->str)
    {
        *s = mx_strnew(0);
        return -1;
    }
    while (strchr_join(s, &lst->str, del))
    {
        rd = read(lst->fd, buf, size);
        if (rd == -1)
            return -2;
        if (!rd)
        {
            lst->eof = true;
            strchr_join(s, &lst->str, 0);
            break;
        }
        lst->str = mx_strndup(buf, rd);
    }
    return mx_strlen(*s);
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd)
{
    static t_fd *head;
    t_fd *lst = head;
    *lineptr = NULL;

    if (!head)
        lst = head = mx_fill_lst(fd);
    else
    {
        while (lst->next && lst->fd != fd)
            lst = lst->next;
        if (lst->fd != fd)
        {
            lst->next = mx_fill_lst(fd);
            lst = lst->next;
        }
    }
    return mx_read(lineptr, lst, buf_size, delim);
}
