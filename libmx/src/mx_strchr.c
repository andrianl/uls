#include "libmx.h"


char *mx_strchr(const char *p, int ch)
{
	char c;

	c = ch;
	for (;; ++p)
	{
		if (*p == c)
			return ((char *)p);
		if (*p == '\0')
			return (NULL);
	}
	/* NOTREACHED */
}
