#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char* perm(mode_t);
void printStat(char*, struct stat*, int, int);

int main(int argc, char **argv)
{
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int showInode = 0; // -i 옵션
    int showPath = 0;  // -Q 옵션

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) showInode = 1;
        else if (strcmp(argv[i], "-Q") == 0) showPath = 1;
        else dir = argv[i];
    }

    if (dir == NULL) dir = ".";

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0) {
            perror(path);
        } else {
            printStat(d->d_name, &st, showInode, showPath);
        }
    }
    closedir(dp);
    exit(0);
}

void printStat(char *file, struct stat *st, int showInode, int showPath)
{
    if (showInode) {
        printf("%lu ", (unsigned long)st->st_ino);
    }

    if (showPath) {
        printf("\"%s\"", file);
    } else {
        printf("%s", file);
    }

    if (S_ISDIR(st->st_mode)) {
        printf("/");
    }

    printf("\n");
}

