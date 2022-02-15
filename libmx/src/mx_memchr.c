#include "libmx.h"

void *mx_memchr(register const void *s, int c, size_t n)
{
  const ubyte *src = (const ubyte *)s;

  // while (n-- > 0)
  while (n--)
  {
    if (*src == c)
      return (void *)src;
    src++;
  }
  return NULL;
}
