#include "libmx.h"
// #include <fcntl.h>
// #include <unistd.h>

char *mx_file_to_str(const char *file)
{
    unsigned size = 0;
    byte buf;

    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        return NULL;
    }
    while (read(fd, &buf, sizeof(buf)) != 0)
    {
        size++;
    }
    if (size <= 0)
    {
        return NULL;
    }
    char *str = (char *)malloc((size + 1) * sizeof(char));
    if (str == NULL)
    {
        return NULL;
    }
    fd = open(file, O_RDONLY);
    read(fd, str, size);
    close(fd);
    str[size] = '\0';
    return str;
}
