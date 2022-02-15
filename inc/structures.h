#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "enums.h"

#define mode_t __mode_t

struct bin_str
{
    size_t len;         /* Number of bytes */
    const char *string; /* Pointer to the same */
};

struct color_ext_type
{
    struct bin_str ext;          /* The extension we're looking for */
    struct bin_str seq;          /* The sequence to output when we do */
    struct color_ext_type *next; /* Next in list */
};

/* Information about filling a column.  */
struct column_info
{
    bool valid_len;
    size_t line_len;
    size_t *col_arr;
};

struct fileinfo
{
    /* The file name.  */
    char *name;

    /* For symbolic link, name of the file linked to, otherwise zero.  */
    char *linkname;

    /* For terminal hyperlinks. */
    char *absolute_name;

    struct stat stat;

    enum filetype filetype;

    /* For symbolic link and long listing, st_mode of file linked to, otherwise
       zero.  */
    mode_t linkmode;

    /* security context.  */
    char *scontext;

    bool stat_ok;

    /* For symbolic link and color printing, true if linked-to file
       exists, otherwise false.  */
    bool linkok;

    /* For long listings, true if the file has an access control list,
       or a security context.  */
    enum acl_type acl_type;

    /* For color listings, true if a regular file has capability info.  */
    bool has_capability;

    /* Whether file name needs quoting. tri-state with -1 == unknown.  */
    int quoted;
};

struct ignore_pattern
{
    const char *pattern;
    struct ignore_pattern *next;
};

struct pending
{
    char *name;
    /* If the directory is actually the file pointed to by a symbolic link we
       were told to list, 'realname' will contain the name of the symbolic
       link, otherwise zero.  */
    char *realname;
    bool command_line_arg;
    struct pending *next;
};