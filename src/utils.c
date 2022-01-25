#include "uls.h"
#include "color.h"

char *get_mode(char *file)
{
    char *modeval = (char *)malloc(sizeof(char) + 1);
    mx_memset(modeval, '\0', 2);
    struct stat buf;  int i = 0;
    if (stat(file, &buf) != 0) return NULL;

    if      (S_ISLNK(buf.st_mode)) {modeval[i] = 'l'; i++;}
    else if (S_ISREG(buf.st_mode)) {modeval[i] = '-'; i++;}
    else if (S_ISDIR(buf.st_mode)) {modeval[i] = 'd'; i++;}
    else if (S_ISCHR(buf.st_mode)) {modeval[i] = 'c'; i++;}
    else if (S_ISBLK(buf.st_mode)) {modeval[i] = 'b'; i++;}
    else if (S_ISFIFO(buf.st_mode)){modeval[i] = 'f'; i++;}
    else {modeval[i] = '-'; i++;};

    return modeval;
}

char *permissions(char *file)
{
    struct stat st;
    char *modeval = (char *)malloc(sizeof(char) * 9 + 1);
    if (stat(file, &st) != 0) return NULL;
    
        mode_t perm = st.st_mode;
        modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
        modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
        modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
        modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
        modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
        modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
        modeval[6] = (perm & S_IROTH) ? 'r' : '-';
        modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
        modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
        modeval[9] = '\0';
        return modeval;
    
}

int flag_buffer(int arguments_count, char **arguments, char *buffer, int *num)
{
    int count = 0;
    for (int i = 1; i < arguments_count; i++)
    {
        if (arguments[i][0] == '-') // check for valid input
        {
            for (int j = 1; j < mx_strlen(arguments[i]); j++)
            {
                buffer[count] = arguments[i][j];
                count++;
            }
            (*num)++;
        }
    }

    return count;
}

int set_bitflag(int count, char *buffer)
{
    int flags = 0x00000000;
    for (int i = 0; i < count; i++)
    {
        if (buffer[i] == 'a')
            flags |= PARAM_A;
        else if (buffer[i] == 'l')
            flags |= PARAM_L;
        else if (buffer[i] == 'R')
            flags |= PARAM_R;
        else if (buffer[i] == 'l')
            flags |= PARAM_L;
        else
        {
            mx_printerr("Invalid option ");
            mx_printerr((const char *)&buffer[i]);
            mx_printerr("\n");
            exit(1);
        }
    }

    return flags;
}

void color_print(char *text, const char *color)
{
    mx_printstr(color);
    mx_printstr(text);
    mx_printstr("\033[0m");
}

void fprint(char *text, const char *color, size_t size)
{
    char *result = (char *)malloc(size * sizeof(char));
    mx_memset(result, ' ', size);
    mx_printstr(color);
    mx_memcpy(result, text, mx_strlen(text));
    mx_printstr(result);
    mx_printstr("\033[0m");
    mx_strdel(&result);
}
    


