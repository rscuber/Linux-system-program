/*************************************************************************
	> File Name: 14.fcntlGetStatus.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 02:06:34 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cmd fd\n");
        exit(1);
    } 
    if (argv[3]) {
        printf("argv[2] = %s\n", argv[2]);
    } else {
        printf("argv[2] not found\n");
    }
    int flags = fcntl(atoi(argv[1]), F_GETFL);
    if (flags < 0) {
        perror("fcntl get flags");
        exit(1);
    }
    switch (flags & O_ACCMODE) {
        case O_RDONLY: printf("read only"); break; 
        case O_WRONLY: printf("write only"); break;
        case O_RDWR: printf("read and write"); break;
        default: printf("invalid access mode\n");
    }

    if (flags & O_APPEND) printf(", append");
    if (flags & O_NONBLOCK) printf(", nonblock");
    putchar(10);

    /*
    printf("flags = %#x\n", flags);
    printf("O_RDONLY = %#x\n", O_RDONLY);
    printf("O_WRONLY = %#x\n", O_WRONLY);
    printf("O_RDWR = %#x\n", O_RDWR);
    printf("O_APPEND = %#x\n", O_APPEND);
    printf("O_NONBLOCK = %#x\n", O_NONBLOCK);
    printf("O_ACCMODE = %#x\n", O_ACCMODE);
    */
    return 0;
}
