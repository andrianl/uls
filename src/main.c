// #include "uls.h"

// void uls(char *directory, int flags)
// {
// }

// int main(int argc, char **argv)
// {

//     struct stat st;
//     DIR *dir = opendir(".");

//     return 0;
// }

// This is the lsd function, yet another C implement of the classic ls, using UNIX functions

// Featuring "stat", "opendir", and "readdir"
// Credits: Jalil Benayachi, ECE PARIS - under MIT license
// contact [at] thejals.com

// Also thanks to some contributors on Stackoverflow

// #define GET_BIT(a, b) (a & ( 1 << b))

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <dirent.h>
// #include <time.h>
// #include <pwd.h>
// #include <grp.h>
// #include "uls.h"

// int main(int argc, char *argv[])
// {

//     //Defining the different components of the program
//     //The directory: it's the folder we're browsing (we'll use an argument (argv) in order to identify it)
//     DIR *thedirectory;
//     //The file: when a file is found in the directory readdir loop, it's going to be called this way.
//     struct dirent *thefile;
//     //The stat: It's how we'll retrieve the stats associated to the file.
//     struct stat thestat;
//     //will be used to determine the file owner & group
//     struct passwd *tf;
//     struct group *gf;

//     //Creating a placeholder for the string.
//     //We create this so later it can be properly adressed.
//     //It's reasonnable here to consider a 512 maximum lenght, as we're just going to use it to display a path to a file,
//     //but we could have used a strlen/malloc combo and declared a simple buf[] at this moment
//     char buf[512];

//     //It's time to assign thedirectory to the argument: this way the user will be able to browse any folder simply by mentionning it
//     //when launching the lsd program.
//     thedirectory = opendir(".");

//     //If a file is found (readdir returns a NOT NULL value), the loop starts/keep going until it has listed all of them.
//     while ((thefile = readdir(thedirectory)) != NULL)
//     {
//         //We sprint "thedirectory/thefile" which defines the path to our file
//         sprintf(buf, "%s/%s", argv[1], thefile->d_name);
//         //Then we use stat function in order to retrieve information about the file
//         stat(buf, &thestat);

//         //Now, we can print a few things !
//         // Here's the right order
//         // [file type] [permissions] [number of hard links] [owner] [group] [size in bytes] [time of last modification] [filename]

//         // [file type]
//         //Let's start with the file type
//         //The stat manual is pretty complete and gives details about st_mode and S_IFMT: http://manpagesfr.free.fr/man/man2/stat.2.html
//         //
//         switch (thestat.st_mode & _S_IFMT)
//         {
//         case _S_IFBLK:
//             printf("b ");
//             break;
//         case _S_IFCHR:
//             printf("c ");
//             break;
//         case _S_IFDIR:
//             printf("d ");
//             break; //It's a (sub)directory
//         case _S_IFIFO:
//             printf("p ");
//             break; //fifo
//         case _S_IFLNK:
//             printf("l ");
//             break; //Sym link
//         case _S_IFSOCK:
//             printf("s ");
//             break;
//         //Filetype isn't identified
//         default:
//             printf("- ");
//             break;
//         }
//         //[permissions]
//         //Same for the permissions, we have to test the different rights
//         //READ http://linux.die.net/man/2/chmod
//         printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
//         printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
//         printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
//         printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
//         printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
//         printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
//         printf((thestat.st_mode & S_IROTH) ? "r" : "-");
//         printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
//         printf((thestat.st_mode & S_IXOTH) ? "x" : "-");

//         // [number of hard links]
//         // Quoting: http://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
//         // "This count keeps track of how many directories have entries for this file.
//         // If the count is ever decremented to zero, then the file itself is discarded as soon as no process still holds it open."
//         printf("\t%lu ", thestat.st_nlink);

//         //[owner]
//         // http://linux.die.net/man/3/getpwuid
//         tf = getpwuid(thestat.st_uid);
//         printf("\t%s ", tf->pw_name);

//         //[group]
//         // http://linux.die.net/man/3/getgrgid
//         gf = getgrgid(thestat.st_gid);
//         printf("\t%s ", gf->gr_name);

//         //And the easy-cheesy part
//         //[size in bytes] [time of last modification] [filename]
//         printf("%zu", thestat.st_size);
//         printf(" %s", thefile->d_name);
//         printf(" %s", ctime(&thestat.st_mtime));
//         int sum = 4 * (thestat.st_mode & 4) + 2 * (thestat.st_mode & 2) +  1 * (thestat.st_mode & 1);
//         printf("Sum is %d", sum);

//     }
//     closedir(thedirectory);
// }

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

#define PARAM_NONE 0 //Since bitwise operations are used later, let's introduce flag=0 when there are no parameters; then - a,-l,-R,-r, defined as 1, 2, 4, 8.
#define PARAM_A 1    //It happens to be 1, 10, 100, 1000 in binary. This is convenient for | and & in operations, such as having both a and r parameters, then flag is 1001.
#define PARAM_L 2    //Flag & PARAM_r can be used to determine whether or not one of these two parameters (e.g., R parameter) is included. If it is zero, there is no r parameter.
#define PARAM_R 4    //Others are similar.
#define PARAM_r 8
#define MAXROWLEN 80
#define PATH_MAX 255

char PATH[PATH_MAX + 1]; //Storage path
int flag;

int g_leave_len = MAXROWLEN;
int g_maxlen;

void my_err(const char *err_string, int line);
void display_dir(char *path);

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line:%d", __LINE__);
    perror(err_string);
    exit(1);
}

void cprint(char *name, mode_t st_mode)
{

    if (S_ISLNK(st_mode)) //Link file
        printf("\033[1;36m%-*s\033[0m", g_maxlen, name);
    else if (S_ISDIR(st_mode) && (st_mode & 000777) == 0777) //Directories with full permissions
        printf("\033[1;34;42m%-*s  \033[0m", g_maxlen, name);
    else if (S_ISDIR(st_mode)) //Catalog
        printf("\033[1;34m%-*s  \033[0m", g_maxlen, name);
    else if (st_mode & S_IXUSR || st_mode & S_IXGRP || st_mode & S_IXOTH) //Executable file
        printf("\033[1;32m%-*s  \033[0m", g_maxlen, name);
    else //Other documents
        printf("%*s  ", g_maxlen, name);
}
void display_attribute(char *name) //Print the - l parameter in the corresponding format
{
    struct stat buf;
    char buff_time[32];
    struct passwd *psd; //Receive the user name of the file owner from this structure
    struct group *grp;  //Get group name
    if (stat(name, &buf) == -1)
    {
        my_err("stat", __LINE__);
    }
    if (S_ISLNK(buf.st_mode))
        printf("l");
    else if (S_ISREG(buf.st_mode))
        printf("-");
    else if (S_ISDIR(buf.st_mode))
        printf("d");
    else if (S_ISCHR(buf.st_mode))
        printf("c");
    else if (S_ISBLK(buf.st_mode))
        printf("b");
    else if (S_ISFIFO(buf.st_mode))
        printf("f");
    //else if (S_ISSOCK(buf.st_mode))
    //    printf("s");
    //Get Print File Owner Rights
    if (buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    //All group permissions
    if (buf.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (buf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (buf.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    //Other people's rights
    if (buf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (buf.st_mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    printf("  ");
    //Get the user name and group name of the file owner based on uid and gid
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    printf("%lu ", buf.st_nlink); //Link number
    printf("%-8s ", psd->pw_name);
    printf("%-8s ", grp->gr_name);

    printf("%lu", buf.st_size);
    strcpy(buff_time, ctime(&buf.st_mtime));
    buff_time[strlen(buff_time) - 1] = '\0'; //Buffe_time has its own newline, so you need to remove the following newline character
    printf("  %s  ", buff_time);
    cprint(name, buf.st_mode);
    printf("\n");
}
void displayR_attribute(char *name) //When l and R are both available, display_attribute is first called to print, and then the function is responsible for recursion.
{
    struct stat buf;

    if (stat(name, &buf) == -1)
    {
        my_err("stat", __LINE__);
    }
    if (S_ISDIR(buf.st_mode))
    {
        display_dir(name);
        free(name);
        char *p = PATH;
        while (*++p)
            ;
        while (*--p != '/')
            ;
        *p = '\0';   //Return the original path to the previous one after each recursion is completed
        chdir(".."); //Jump to the top level of the current directory
        return;
    }
}
void display_single(char *name) //Print document
{
    int len;
    struct stat buf;
    if (stat(name, &buf) == -1)
    {
        return;
    }

    if (g_leave_len < g_maxlen)
    {
        printf("\n");
        g_leave_len = MAXROWLEN;
    }

    cprint(name, buf.st_mode); //Display different colors according to different types of files
    g_leave_len = g_leave_len - (g_maxlen + 2);
}

void displayR_single(char *name) //Print the file name and call display_dir when the - R parameter is present
{
    int len;
    struct stat buf;
    if (stat(name, &buf) == -1)
    {
        return;
    }
    if (S_ISDIR(buf.st_mode))
    {
        printf("\n");

        g_leave_len = MAXROWLEN;

        display_dir(name);
        free(name); //Release space from previous filenames[i]
        char *p = PATH;

        while (*++p)
            ;
        while (*--p != '/')
            ;
        *p = '\0';
        chdir(".."); //Return to the upper directory
    }
}

void display(char **name, int count) //Call different functions according to flag
{
    switch (flag)
    {
        int i;
    case PARAM_r:
    case PARAM_NONE:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') //Exclude...,..., and hide files
                display_single(name[i]);
        }
        break;
    case PARAM_r + PARAM_A:
    case PARAM_A:
        for (i = 0; i < count; i++)
        {
            display_single(name[i]);
        }
        break;
    case PARAM_r + PARAM_L:
    case PARAM_L:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                display_attribute(name[i]);
            }
        }
        break;
    case PARAM_R + PARAM_r:
    case PARAM_R:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                display_single(name[i]);
            }
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') //Exclude the directories of'. 'and'.' to prevent the dead cycle. The same below
            {
                displayR_single(name[i]);
            }
        }
        break;
    case PARAM_L + PARAM_r + PARAM_R:
    case PARAM_R + PARAM_L:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                display_attribute(name[i]);
            }
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                displayR_attribute(name[i]);
            }
        }
        break;
    case PARAM_A + PARAM_r + PARAM_R:
    case PARAM_R + PARAM_A:
        for (i = 0; i < count; i++)
        {
            display_single(name[i]);
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                displayR_single(name[i]);
            }
        }
        break;

    case PARAM_A + PARAM_L + PARAM_r:
    case PARAM_A + PARAM_L:
        for (i = 0; i < count; i++)
        {
            display_attribute(name[i]);
        }
        break;
    case PARAM_A + PARAM_L + PARAM_R + PARAM_r:
    case PARAM_A + PARAM_L + PARAM_R:
        for (i = 0; i < count; i++)
        {
            display_attribute(name[i]);
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')
            {
                displayR_attribute(name[i]);
            }
        }
        break;
    default:
        break;
    }
}

void display_dir(char *path) //This function is used to process directories
{
    DIR *dir;           //Accept the file descriptor returned by opendir
    struct dirent *ptr; //Structures that accept readdir returns
    int count = 0;
    //char filenames[300][PATH_MAX+1],temp[PATH_MAX+1]; here is the optimized code, because of the variables defined in the function
    //It allocates space on the stack, so it consumes space on the stack when it is called many times, which eventually leads to stack overflow. The performance on linux is that the core has been dumped.
    //And some directories have far more than 300 files.

    if ((flag & PARAM_R) != 0) //As an obsessive-compulsive disorder, no format problems are allowed.
    {
        int len = strlen(PATH);
        if (len > 0)
        {
            if (PATH[len - 1] == '/')
                PATH[len - 1] = '\0';
        }
        if (path[0] == '.' || path[0] == '/')
        {
            strcat(PATH, path);
        }
        else
        {
            strcat(PATH, "/");
            strcat(PATH, path);
        }
        printf("%s:\n", PATH);
    }
    //Get the number of files and the longest file name length
    dir = opendir(path);
    if (dir == NULL)
        my_err("opendir", __LINE__);
    g_maxlen = 0;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (g_maxlen < strlen(ptr->d_name))
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);
    char **filenames = (char **)malloc(sizeof(char *) * count), temp[PATH_MAX + 1]; //Dynamic allocation of storage space on the heap is achieved by the number of files in the directory. First, an array of pointers is defined.
    for (int i = 0; i < count; i++)                                                 //Then let each pointer in the array point to the allocated space in turn. Here is the optimization, which is effective.
    {                                                                               //It prevents stack overflow and allocates memory dynamically, which saves more space.
        filenames[i] = (char *)malloc(sizeof(char) * PATH_MAX + 1);
    }

    int i, j;
    //Get all file names in this directory
    dir = opendir(path);
    for (i = 0; i < count; i++)
    {
        ptr = readdir(dir);
        if (ptr == NULL)
        {
            my_err("readdir", __LINE__);
        }
        strcpy(filenames[i], ptr->d_name);
    }
    closedir(dir);
    //Sorting File Names by Bubble Method
    if (flag & PARAM_r) //Reverse sorting of-r parameters
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(filenames[j], filenames[j + 1]) < 0)
                {
                    strcpy(temp, filenames[j]);
                    strcpy(filenames[j], filenames[j + 1]);
                    strcpy(filenames[j + 1], temp);
                }
            }
        }
    }
    else //Forward sort
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (strcmp(filenames[j], filenames[j + 1]) > 0)
                {
                    strcpy(temp, filenames[j]);
                    strcpy(filenames[j], filenames[j + 1]);
                    strcpy(filenames[j + 1], temp);
                }
            }
        }
    }

    if (chdir(path) < 0)
    {
        my_err("chdir", __LINE__);
    }

    display(filenames, count);
    if ((flag & PARAM_L == 0 && !(flag | PARAM_R)))
        printf("\n");
}

int main(int argc, char **argv)
{
    int i, j, k = 0, num = 0;
    char param[32] = "";                                     //Used to save command line parameters
    char *path[1];                                           //Save the path, which I don't want to define as an array of pointers, but it's the only way to define a function parameter corresponding to the char ** type that follows
    path[0] = (char *)malloc(sizeof(char) * (PATH_MAX + 1)); //Since it's a pointer type, we need to allocate space PATH_MAX to it. It's a system-defined macro with a value of 4096. Strictly, add 1 to store'\0'.
    flag = PARAM_NONE;                                       //Initialize flag=0 (since flag is a full play variable, you don't need to initialize)
    struct stat buf;                                         //The structure and stat,stat, in sys/types.h, sys/stat.h, unistd.h, specific man 2 stat

    //Command line parameter parsing, save the following parameters to param
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (j = 1; j < strlen(argv[i]); j++)
            {
                param[k] = argv[i][j];
                k++;
            }
            num++;
        }
    }
    param[k] = '\0';

    /* Judgement parameter */
    for (i = 0; i < k; i++)
    {
        if (param[i] == 'a')
            flag |= PARAM_A;
        else if (param[i] == 'l')
            flag |= PARAM_L;
        else if (param[i] == 'R')
            flag |= PARAM_R;
        else if (param[i] == 'r')
            flag |= PARAM_r;
        else
        {
            printf("my_ls:invalid option -%c\n", param[i]);
            exit(0);
        }
    }

    //If no target file or directory is entered, the current directory is displayed
    if (num + 1 == argc)
    {
        strcpy(path[0], ".");
        display_dir(path[0]);
        return 0;
    }

    i = 1;
    do
    {
        if (argv[i][0] == '-')
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path[0], argv[i]);
            //Determine whether a directory or file exists
            if (stat(argv[i], &buf) == -1)
            {
                my_err("stat", __LINE__); //The compiler's built-in macro inserts the current source line number
            }
            if (S_ISDIR(buf.st_mode)) //Determine whether it is a catalog
            {
                display_dir(path[0]);
                i++;
            }
            else
            {
                display(path, 1);
                i++;
            }
        }
    } while (i < argc);
    printf("\n");

    return 0;
}
