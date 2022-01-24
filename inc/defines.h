#pragma once

#define _S_IFMT   0170000   //bitmask for the file type bitfields
#define _S_IFSOCK 0140000 //socket
#define _S_IFLNK  0120000 //symbolic link
#define _S_IFREG  0100000 //regular file
#define _S_IFBLK  0060000 //block device
#define _S_IFDIR  0040000 //directory
#define _S_IFCHR  0020000 //character device
#define _S_IFIFO  0010000 //FIFO
#define _S_ISUID  0004000 //set UID bit
#define _S_ISGID  0002000 //set - group - ID bit(see below)
#define _S_ISVTX  0001000 //sticky bit(see below)
#define _S_IRWXU  00700     //mask for file owner permissions
#define _S_IRUSR  00400 //owner has read permission
#define _S_IWUSR  00200 //owner has write permission
#define _S_IXUSR  00100 //owner has execute permission
#define _S_IRWXG  00070     //mask for group permissions
#define _S_IRGRP  00040 //group has read permission
#define _S_IWGRP  00020 //group has write permission
#define _S_IXGRP  00010 //group has execute permission
#define _S_IRWXO  00007     //mask for permissions for others (not in group)
#define _S_IROTH  00004 //others have read permission
#define _S_IWOTH  00002 //others have write permission
#define _S_IXOTH  00001 //others have execute permission