#include "libmx.h"

unsigned long mx_mod(int num)
{
	return (unsigned long)(num < 0) ? (unsigned long)num * -1 : num;
}
