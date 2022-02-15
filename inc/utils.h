#pragma once

#include "structures.h"
#include "wizaral.h"

char *permissions(char *file);
char *mode(mode_t m);
char *user_name(struct stat s);
char *date(__time_t stctime);
char *mx_path_to_file(char *dir_name, char *d_name);
char *mx_get_size_h(off_t st_size, uint8_t *flags);
uint16_t mx_winsize(info *info);
size_t mx_get_inode_bsize_len(offset *off);
int mx_get_tabs(int size);
int mx_get_data_len(info *info, dir *dir, file *file, bool longest);
char *mx_get_file_name(char *av);
