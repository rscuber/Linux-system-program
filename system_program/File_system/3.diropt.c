/*************************************************************************
	> File Name: 3.diropt.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 23 Jun 2021 10:18:33 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void printDir(char *dirname) {
    char pathname[1024];
    DIR *dir = opendir(dirname);
    struct dirent *dp;
    struct stat st;
    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while (dp = readdir(dir)) {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;
        sprintf(pathname, "%s/%s", dirname, dp->d_name);
        int s = stat(pathname, &st);
        if (s < 0) {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", dp->d_name);
        if (S_ISDIR(st.st_mode)) {
            printDir(pathname);
        }
    }
    putchar(10);
    closedir(dir);
    return ;
}

int main(int argc, char *argv[]) {
    if (argc - 2) {
        fprintf(stdout, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printDir(argv[1]);
    return 0;
}
