/*************************************************************************
	> File Name: 2.open.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Sat 12 Jun 2021 06:16:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\033[0;1;31mUsage: cmd filename\033[0m" "\n");
    }
    int fd1 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    /*
    int fd = open(
        argv[1], O_WRONLY | O_CREAT, 
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
    );
    */
    //printf("%d\n", errno);
    if (fd1 < 0) {
        perror("open1");
        exit(-1);
    } else {
        perror("open1");
    }
    printf("fd1 = %d\n", fd1);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        perror("open2");
        exit(-1);
    } else {
        perror("open2");
    }
    printf("fd2 = %d\n", fd2);
    close(fd1);
    int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd3 < 0) {
        perror("open3");
        exit(-1);
    } else {
        perror("open3");
    }
    printf("fd3 = %d\n", fd3);
    close(fd2);
    close(fd3);
    return 0;
}
