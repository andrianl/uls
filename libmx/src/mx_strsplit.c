#include "libmx.h"

char **mx_strsplit(char const *s, char c)
{

    if (!s)
        return NULL;

    unsigned words, chars = 0;

    words = mx_count_words(s, c);
    char **arr = (char **)malloc(sizeof(char *) * (words + 1));

    for (unsigned i = 0; i < words; i++)
    {
        chars = 0;
        while (*s == c && *s)
            s++;
        while (*s != c && *s)
        {
            chars++;
            s++;
        }
        arr[i] = malloc(sizeof(char) * (chars + 1));
        arr[i] = mx_strncpy(arr[i], s - chars, chars);
        arr[i][chars] = '\0';
    }
    arr[words] = NULL;

    if (arr)
        return arr;
    return NULL;
}
