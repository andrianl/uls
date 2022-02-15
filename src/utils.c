#include "utils.h"
#include "libmx.h"

char *permissions(char *file)
{
    struct stat st;
    char *permission = (char *)malloc(sizeof(char) * 9 + 1);
    // char permission[10];
    if (stat(file, &st) != 0)
        return NULL;

    mode_t perm = st.st_mode;
    permission[0] = (perm & S_IRUSR) ? 'r' : '-';
    permission[1] = (perm & S_IWUSR) ? 'w' : '-';
    permission[2] = (perm & S_IXUSR) ? 'x' : '-';
    permission[3] = (perm & S_IRGRP) ? 'r' : '-';
    permission[4] = (perm & S_IWGRP) ? 'w' : '-';
    permission[5] = (perm & S_IXGRP) ? 'x' : '-';
    permission[6] = (perm & S_IROTH) ? 'r' : '-';
    permission[7] = (perm & S_IWOTH) ? 'w' : '-';
    permission[8] = (perm & S_IXOTH) ? 'x' : '-';
    permission[9] = '\0';
    return permission;
}

char *mode(mode_t m)
{
    char *str = mx_strnew(11);
    // char str[12];
    str[0] = '\0';
    if (S_ISREG(m))
        mx_strcpy(str, "-");
    else if (S_ISDIR(m))
        mx_strcpy(str, "d");
    else if (S_ISCHR(m))
        mx_strcpy(str, "c");
    else if (S_ISBLK(m))
        mx_strcpy(str, "b");
    else if (S_ISFIFO(m))
        mx_strcpy(str, "f");
    else if (S_ISLNK(m))
        mx_strcpy(str, "l");
    //    else if(MX_ISSCK(m))
    //    	    mx_strcpy(str,"n");

    mx_strcat(str, m & S_IRUSR ? "r" : "-");
    mx_strcat(str, m & S_IWUSR ? "w" : "-");
    mx_strcat(str, m & S_IXUSR ? "x" : "-");

    mx_strcat(str, m & S_IRGRP ? "r" : "-");
    mx_strcat(str, m & S_IWGRP ? "w" : "-");
    mx_strcat(str, m & S_IXGRP ? "x" : "-");

    mx_strcat(str, m & S_IROTH ? "r" : "-");
    mx_strcat(str, m & S_IWOTH ? "w" : "-");
    mx_strcat(str, m & S_IXOTH ? "x" : "-");

    return str;
}

char *user_name(struct stat s)
{
    struct passwd *passwd;
    char *name = NULL;

    passwd = getpwuid(s.st_uid);
    name = mx_strdup(passwd->pw_name);

    return name;
}

char *date(__time_t st_ctime)
{
    char *temp = ctime(&st_ctime);
    char *str_date = mx_strnew(13);
    mx_memcpy(str_date, temp + 4, 12);
    return str_date;
}

char *path_to_file(char *dir_name, char *d_name)
{
    char *path_to_file_tmp = mx_strjoin(dir_name, "/");
    char *path_to_file = mx_strjoin(path_to_file_tmp, d_name);
    free(path_to_file_tmp);
    return path_to_file;
}

int get_size(struct stat *file_st)
{
    return file_st->st_size;
}

int get_serial_num(char *path, char *dir)
{
    char full_path[PATH_MAX] = "";
    struct stat file_st;

    mx_strcpy(full_path, path);
    mx_strcat(full_path, dir);

    stat(full_path, &file_st);

    return file_st.st_ino;
}

char *mx_get_size_h(off_t st_size, uint8_t *flags)
{
    if (flags[0]) // here must be flag h
    {
        char *str = NULL;
        char *tmp = NULL;
        if (st_size < 1000)
        {
            str = mx_strjoin(mx_itoa(st_size), "B");
            return str;
        }
        else if (st_size >= 1000 && st_size < 1000000)
        {
            tmp = mx_double_to_str((double)st_size / BIBYTE);
            str = mx_strjoin(tmp, "K");
            mx_strdel(&tmp);
            return str;
        }
        else if (st_size >= 1000000 && st_size < 1000000000)
        {
            tmp = mx_double_to_str((double)st_size / BIBYTE / BIBYTE);
            str = mx_strjoin(tmp, "M");
            mx_strdel(&tmp);
            return str;
        }
        else if (st_size >= 1000000000 && st_size < 1000000000000)
        {
            tmp = mx_double_to_str((double)st_size / BIBYTE / BIBYTE / BIBYTE);
            str = mx_strjoin(tmp, "G");
            mx_strdel(&tmp);
            return str;
        }
    }
    return mx_itoa(st_size);
}

uint16_t mx_winsize(info *info)
{
    if (info->output_dst == 0)
    {
        int fd = open("/dev/tty", O_RDWR);
        struct winsize ws;

        ioctl(fd, TIOCGWINSZ, &ws);
        close(fd);
        return ws.ws_col;
    }
    return 80;
}

size_t mx_get_inode_bsize_len(offset *off)
{
    return off->inode + off->bsize + (off->inode > 0) + (off->bsize > 0);
}

void mx_make_inode_bsize(offset *off, char *str, printable *print, lengths *len)
{
    mx_memcpy(str + off->inode - len->inode, print->inode, len->inode);
    mx_memcpy(str + off->inode + (off->inode > 0) + off->bsize - len->bsize,
              print->bsize, len->bsize);
}

int mx_get_tabs(int size)
{
    int count = 0;

    while (size >= 8)
    {
        ++count;
        size -= 8;
    }

    return count;
}

void mx_dummy(dir *dir, file *file, struct stat *st)
{
    (void)dir;
    (void)file;
    (void)st;
}

int mx_get_data_len(info *info, dir *dir, file *file, bool longest)
{
    if (longest)
    {
        return dir->off.name + mx_get_inode_bsize_len(&dir->off) + (info->get.suffix != mx_dummy);
    }

    return file->length.name + mx_get_inode_bsize_len(&dir->off) + file->length.suffix;
}

char *mx_get_file_name(char *av)
{
    for (char *temp = mx_strchr(av, '/'); temp; temp = mx_strchr(av, '/'))
    {
        av = temp + 1;
    }
    return av;
}