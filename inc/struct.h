#pragma once

#include <stdint.h>
#include <dirent.h>

typedef struct stat t_stat;

typedef struct s_vector
{
    size_t cap;   // capacity
    size_t size;  // current size
    size_t bytes; // size of item
    uint8_t *arr; // array of items
} t_vector;

struct s_offset
{
    size_t columns;   // number of columns in C out
    size_t rows;      // number of rows in C out
    size_t width;     // terminal width
    size_t x;         // current position in line
    size_t name_tabs; // tabs in longest filename

    uint8_t inode; // length of longest inode
    uint8_t bsize; // length of longest block size
    uint8_t links; // length of longest amount of links
    uint8_t user;  // length of longest user name/id
    uint8_t grp;   // length of longest group name/id
    uint8_t size;  // length of longest size
    uint8_t name;  // length of longest filename
};

struct s_dir
{
    DIR *dir;      // pointer to opened directory
    char *name;    // current directory
    size_t len;    // length of directory name
    int64_t total; // total block count

    struct dirent *file; // current file on reading
    char *filename;      // name of current file ["dirname/filename"]

    t_vector array;      // struct for manage array of files
    struct s_offset off; // offsets in current directory
};
