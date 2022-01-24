#include "libmx.h"

bool mx_isspace(char c)
{
	return c == ' ' || (c > 8 && c < 14);
}
