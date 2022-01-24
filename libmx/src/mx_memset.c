#include "libmx.h"

void *mx_memset(void *b, int c, size_t len)
{
  register ubyte *ptr = (ubyte *)b;
  while (len--)
    *ptr++ = c;
  return b;
}
