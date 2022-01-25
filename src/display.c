#include "uls.h"
#include "color.h"

extern char PATH[PATH_MAX + 1];
extern int g_leave_len;
extern int g_maxlen;
extern int bitflag;



void display_dir(char *path) //This function is used to process directories
{
    DIR *dir;           //Accept the file descriptor returned by opendir
    struct dirent *ptr; //Structures that accept readdir returns
    int count = 0;
    //char filenames[300][PATH_MAX+1],temp[PATH_MAX+1]; here is the optimized code, because of the variables defined in the function
    //It allocates space on the stack, so it consumes space on the stack when it is called many times, which eventually leads to stack overflow. The performance on linux is that the core has been dumped.
    //And some directories have far more than 300 files.

    if ((bitflag & PARAM_R) != 0) //As an obsessive-compulsive disorder, no format problems are allowed.
    {
        int len = mx_strlen(PATH);
        if (len > 0)
        {
            if (PATH[len - 1] == '/')
                PATH[len - 1] = '\0';
        }
        if (path[0] == '.' || path[0] == '/')
        {
            mx_strcat(PATH, path);
        }
        else
        {
            mx_strcat(PATH, "/");
            mx_strcat(PATH, path);
        }
        //printf("%s:\n", PATH);
        mx_printstr(PATH); mx_printstr(":\n");
    }
    //Get the number of files and the longest file name length
    dir = opendir(path);
    if (dir == NULL)
        my_err("opendir", __LINE__);
    g_maxlen = 0;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (g_maxlen < mx_strlen(ptr->d_name))
            g_maxlen = mx_strlen(ptr->d_name);
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
        mx_strcpy(filenames[i], ptr->d_name);
    }
    closedir(dir);
    //Sorting File Names by Bubble Method
    if (bitflag & PARAM_r) //Reverse sorting of-r parameters
    {
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - 1 - i; j++)
            {
                if (mx_strcmp(filenames[j], filenames[j + 1]) < 0)
                {
                    mx_strcpy(temp, filenames[j]);
                    mx_strcpy(filenames[j], filenames[j + 1]);
                    mx_strcpy(filenames[j + 1], temp);
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
                if (mx_strcmp(filenames[j], filenames[j + 1]) > 0)
                {
                    mx_strcpy(temp, filenames[j]);
                    mx_strcpy(filenames[j], filenames[j + 1]);
                    mx_strcpy(filenames[j + 1], temp);
                }
            }
        }
    }

    if (chdir(path) < 0)
    {
        my_err("chdir", __LINE__);
    }

    display(filenames, count);
    if (((bitflag & PARAM_L) == 0 && !((bitflag | PARAM_R))))
        mx_printchar('\n');
}

void display_single(char *name) //print file
{
    int len;
    struct stat buf;
    if (stat(name, &buf) == -1)
    {
        return;
    }

    if (g_leave_len < g_maxlen)
    {
        mx_printchar('\n');
        g_leave_len = MAXROWLEN;
    }
    cprint(name, buf.st_mode); //display different colors according to different types of files
    g_leave_len = g_leave_len - (g_maxlen + 2);
}

void displayR_single(char *name)
{
    int len;
    struct stat buf;
    if (stat(name, &buf) == -1)
    {
        return;
    }
    if (S_ISDIR(buf.st_mode))
    {
        mx_printchar('\n');
        g_leave_len = MAXROWLEN;
        display_dir(name);
        free(name); //free  space from previous filenames
        char *p = PATH;

        while (*++p){};
        while (*--p != '/'){};
        
        *p = '\0';
        chdir(".."); //return to the upper directory
    }
}


void display_attribute(char *name) // print ls -l in corresponding format
{
    struct stat buf;
    char buff_time[32];
    struct passwd *psd; // ger user name of the file owner from this structure
    struct group *grp; //get group
    if (stat(name, &buf) == -1)
    {
        my_err("stat", __LINE__);
    }

    //else if (S_ISSOCK(buf.st_mode)) mx_printchar('s'); // not working

    char *mode = get_mode(name);
    mx_printstr(mode); mx_strdel(&mode);
    char *permission = permissions(name);
    mx_printstr(permission); mx_strdel(&permission);
    mx_printchar(' ');

    //get the user and group name of the file owner based on uid and gid
    psd = getpwuid(buf.st_uid);
    grp = getgrgid(buf.st_gid);
    mx_printint(buf.st_nlink); mx_printchar(' '); // link number
   
    //for correct output need 8 symblos
    mx_printstr(psd->pw_name); mx_printchar(' '); // printf("%-8s ", psd->pw_name);
    mx_printstr(grp->gr_name); mx_printchar(' '); // printf("%-8s ", grp->gr_name);

    mx_printint(buf.st_size); // size of the file
    mx_strcpy(buff_time, ctime(&buf.st_mtime));
    buff_time[mx_strlen(buff_time) - 1] = '\0'; //Buffe_time has its own newline, so you need to remove the following newline character
    mx_printchar(' '); mx_printstr(buff_time); mx_printchar(' '); // print time
    cprint(name, buf.st_mode);
    mx_printchar('\n');
}

void displayR_attribute(char *name)
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
        while (*++p) {};
        while (*--p) {}; //Return the original path to the previous one after each recursion is completed
        *p = '\0';
        chdir(".."); //Jump to the top level of the current directory
        return;
    }   
}

void cprint(char *name, mode_t st_mode)
{
    // maybe will be problems with formating

    //Link file
    if (S_ISLNK(st_mode)) fprint(name, Cyan, g_maxlen);
    //Directories with full permissions
    else if (S_ISDIR(st_mode) && (st_mode & 000777) == 0777) fprint(name, Cyan, g_maxlen);
    //Catalog 
    else if (S_ISDIR(st_mode)) fprint(name, Cyan, g_maxlen);
    //Executable file
    else if (st_mode & S_IXUSR || st_mode & S_IXGRP || st_mode & S_IXOTH) fprint(name, Cyan, g_maxlen);
    //Other documents
    else {fprint(name, White, g_maxlen); mx_printchar(' ');}
}

void display(char **name, int count)
{

    switch (bitflag)
    {
        int i;
    case PARAM_r:
    case  PARAM_NONE:
        for(i = 0; i < count; i++)
        {   //Exclude...,..., and hide files
            if (name[i][0] !=  '.') display_single(name[i]);
        }
        break;
    case   PARAM_r + PARAM_A:
    case PARAM_A:
        for (i = 0; i < count; i++) display_single(name[i]);
        break;
    case PARAM_r + PARAM_L:
    case PARAM_L:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.')  display_attribute(name[i]);
        }
        break;
    case PARAM_R + PARAM_r:
    case PARAM_R:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') display_single(name[i]);
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') displayR_single(name[i]);
        }
        break; 
    case PARAM_L + PARAM_r + PARAM_R:
    case PARAM_R + PARAM_L:
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') display_attribute(name[i]);
            
        }
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') displayR_attribute(name[i]);
        }
        break;
    case PARAM_A + PARAM_r + PARAM_R:
    case PARAM_R + PARAM_A:
        for (i = 0; i < count; i++) display_single(name[i]);
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') displayR_single(name[i]);
        }
        break;

    case PARAM_A + PARAM_L + PARAM_r:
    case PARAM_A + PARAM_L:
        for (i = 0; i < count; i++) display_attribute(name[i]);
        break;
    case PARAM_A + PARAM_L + PARAM_R + PARAM_r:
    case PARAM_A + PARAM_L + PARAM_R:
        for (i = 0; i < count; i++) display_attribute(name[i]);
        for (i = 0; i < count; i++)
        {
            if (name[i][0] != '.') displayR_attribute(name[i]);
            
        }
        break;
    default:
        break;
    }
}


