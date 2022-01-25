#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include "defines.h"

#include "libmx.h"
#include "struct.h"

#define PARAM_NONE 0 //Since bitwise operations are used later, let's introduce flag=0 when there are no parameters; then - a,-l,-R,-r, defined as 1, 2, 4, 8.
#define PARAM_A 1    //It happens to be 1, 10, 100, 1000 in binary. This is convenient for | and & in operations, such as having both a and r parameters, then flag is 1001.
#define PARAM_L 2    //Flag & PARAM_r can be used to determine whether or not one of these two parameters (e.g., R parameter) is included. If it is zero, there is no r parameter.
#define PARAM_R 4    //Others are similar.
#define PARAM_r 8
#define MAXROWLEN 80
#define PATH_MAX 255



char *get_mode(char *file);
char *permissions(char *file);
int flag_buffer(int arguments_count, char **arguments, char *buffer, int *num);
int set_bitflag(int count, char *buffer);


void my_err(const char *err_string, int line);
void color_print(char *text, const char *color);
void fprint(char *text, const char *color, size_t size);

void display_dir(char *path);
void display_single(char *name);
void displayR_single(char *name);
void display_attribute(char *name);
void displayR_attribute(char *name);
void cprint(char *name, mode_t st_mode);
void display(char **name, int count);


#endif // ULS_H
