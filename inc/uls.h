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

char *permissions(char *file);

#endif // ULS_H
