///------------------------------------------------///
///   Class:          <UNIX SYSTEM PROGRAMMING>    ///
///   Description:    <DU COMMAND>                 ///
///   Author:         <Kori Vernon>                ///
///   Date:           <03/06/2021>                 ///
///------------------------------------------------///
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>

#define TRUE 1
#define PATH "."

int blkSz( char *directory);
/*
 * The block size function is passed a directory that contains
 * and returns the block size of the directory in which it
 * is passed.
*/

void check_dir(struct dirent *entry,  char *dir,  char *d_name);
/*
 * The check directory function is passed the entire directory name
 * and then recusively calls the find_dir function to recursively search
 * ONLY the files. 
*/

void find_dir( char *dir);
/*
 * The find directory function searches for all of the directories.
*/

int blkSz( char *d)
{
    int sz = 0;
    struct dirent *dir;
    struct stat info;
    DIR *currdir = opendir(d);
    while ((dir = readdir(currdir)) != NULL)
    {
        if (dir->d_name[0] != '.')
        {
            //ignore all of the hidden files
            char start[PATH_MAX + 1]; // starting path
            strcpy(start, d);
            if (d[strlen(d) - 1] != '/')
            {
                //if the directory's last char is not '/' then concat
                strcat(start, "/");
            }
            strcat(start, dir->d_name);
            stat(start, &info);
            sz += info.st_blocks;
        }
    }
    return sz;
}

void check_dir(struct dirent *dp,  char *dir,  char *d_name)
{
    // if this is a directory then look
    if (dp->d_type & DT_DIR)
    {
        if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0)
        {
            //while not ..
            char nextDir[PATH_MAX];
            //format and store dir_name/d_name in path then search
            snprintf(nextDir, PATH_MAX, "%s/%s", dir, d_name);
            //Recursively call find_dir ot locate more directories
            find_dir(nextDir);
        }
    }
}

void find_dir( char *dir)
{
    DIR *currdir;
    currdir = opendir(dir);
    while (TRUE)
    {
        struct dirent *dp = readdir(currdir);
         char *d_name;
        if (!dp)
        {
            // determine the blocksize of the directory
            int blkSize = blkSz(dir);
            // print in the format 0    ./DIRNAME
            printf("%d\t%s\n", blkSize, dir);
            break;
        }
        d_name = dp->d_name;
        // check the directory
        check_dir(dp, dir, d_name);
    }
}

int main()
{
    find_dir(PATH);
    return EXIT_SUCCESS;
}
