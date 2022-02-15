#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <time.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "libmx.h"

#define PATH_MAX 4096
#define BIBYTE 1024

typedef enum time_type
{
    last_access = 0,
    modification = 1,
    change = 2,
    creation = 3,
} time_type;

typedef struct lengths
{
    uint8_t inode;
    uint8_t bsize;
    uint8_t links;
    uint8_t user;
    uint8_t grp;
    uint8_t size;
    uint8_t name;
    uint8_t suffix;
    uint8_t arrow;
} lengths;

typedef struct offset
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
} offset;

typedef struct printable
{
    char *inode;
    char *bsize;
    char *links;
    char *user;
    char *grp;
    char *size;
    char *time;
    char *name;
    char *arrow;
    char suffix;
    char access[12];
} printable;

typedef struct file
{
    char *name;
    char *path;
    uint16_t mode;
    int64_t size;
    struct timespec timespec;
    struct printable fields;
    struct lengths length;
    struct stat file_stat;

} file;

typedef struct dir
{
    DIR *dir;      // pointer to opened directory
    char *name;    // current directory
    size_t len;    // length of directory name
    int64_t total; // total block count

    struct dirent *file; // current file on reading
    char *filename;      // name of current file ["dirname/filename"]

    t_vector array; // struct for manage array of files
    offset off;     // offsets in current directory
} dir;

// typedef struct uls
// {
//     char *curr_year;
//     char *curr_dir;
//     char *separator;
//     bool (*cmp_func)(void *, void *);
//     uint8_t flags[17];
//     uint8_t obj_num;
//     uint8_t namlen;
//     t_list *dirs;
//     t_list *non_existent;
//     t_list *files;
//     t_list *contents;
// } uls;

typedef struct object
{
    int serial_num;
    char *d_name;
    char file_type;
    char *permissions;
    uint16_t links;
    char *owner;
    char *group;
    int size;
    char *size_h;
    char *time;
    struct timespec time_sec;
} object;

typedef struct gets
{
    void (*name)(dir *, file *, struct stat *);
    void (*inode)(dir *, file *, struct stat *);
    void (*bsize)(dir *, file *, struct stat *);
    void (*access)(dir *, file *, struct stat *);
    void (*links)(dir *, file *, struct stat *);
    void (*user)(dir *, file *, struct stat *);
    void (*grp)(dir *, file *, struct stat *);
    void (*size)(dir *, file *, struct stat *);
    void (*time)(dir *, file *, struct stat *);
    void (*suffix)(dir *, file *, struct stat *);
    void (*arrow)(dir *, file *, struct stat *);
} gets;

typedef struct info
{
    void (*write)(struct info *, dir *);           // determines type of print
    struct dirent *(*read)(DIR *);          // filter of hiden files
    int (*cmp)(const void *, const void *); // compare function in sort
    void (*print_total)(struct info *, dir *);     // print total bsize
    void (*print_name)(file *);             // out fname colored/normal
    void (*recursion)(struct info *, dir *);       // recursion in directories

    gets get;           // functions for getting files info
    uint8_t time_len;   // length of time in -l format
    bool output_dst;    // 0 - terminal | 1 - file or other process
    bool return_val;    // 0 - good | 1 - any error
    bool reverse;       // 0 - normal | 1 - reversed
    bool filedir;       // 0 - default | 1 - dir like file
    time_type timetype; // data/time type for -[tlgno]

    t_vector files; // files from arguments
    t_vector dirs;  // dirs from arguments
} info;
