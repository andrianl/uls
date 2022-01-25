#include "uls.h"

void my_err(const char *err_string, int line)
{
    mx_printerr("line:");
    mx_printint(__LINE__);
    perror(err_string);
    exit(1);
}
