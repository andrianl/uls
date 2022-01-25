#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>
#include "libmx.h"
#include "uls.h"

#define PARAM_NONE 0 //Since bitwise operations are used later, let's introduce flag=0 when there are no parameters; then - a,-l,-R,-r, defined as 1, 2, 4, 8.
#define PARAM_A 1    //It happens to be 1, 10, 100, 1000 in binary. This is convenient for | and & in operations, such as having both a and r parameters, then flag is 1001.
#define PARAM_L 2    //Flag & PARAM_r can be used to determine whether or not one of these two parameters (e.g., R parameter) is included. If it is zero, there is no r parameter.
#define PARAM_R 4    //Others are similar.
#define PARAM_r 8
#define MAXROWLEN 80
#define PATH_MAX 255


char PATH[PATH_MAX + 1];
int g_leave_len = MAXROWLEN;
int g_maxlen;
int bitflag = PARAM_NONE;

int main(int argc, char **argv)
{
    //int i, j, count = 0, num = 0;
    int count = 0; //number of flags 
    int num = 0;
    char flags[32] = {'\0'}; //buffer for store flags
   // mx_memset(flags, '\0', 32);
    char *path[1]; //path to the folder
    path[0] = (char *)malloc(sizeof(char) * PATH_MAX + 1);
    struct stat buf; // system struct stat to store info about dir or file

    count = flag_buffer(argc, argv, flags, &num); // init flags buffer with flags and  count number of
    

    bitflag = set_bitflag(count, flags); // set another buffer, but flags stored in bits

    if ((num + 1) == argc)
    {
        mx_strcpy(path[0], ".");
        display_dir(path[0]);
        return 0;
    }


    int i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
        {
            //mx_strcpy(path[0],argv[i]);
            mx_strcpy(path[0], argv[1]);
            //Determine wheter a directory or file exists
            if (stat(argv[i], &buf) == -1)
            {
                my_err("stat", __LINE__); // compilers built-in macro inserts the current source line number
            }
            if (S_ISDIR(buf.st_mode))
            {
                display_dir(path[0]);
                i++;
            }
            else
            {
                //display(path, 1);
                mx_printstr("else {display}");
                i++;
            }
        }
    }
    
    mx_printchar('\n');
    mx_strdel(path);
    return 0;
}
