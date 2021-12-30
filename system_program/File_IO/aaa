/*************************************************************************
	> File Name: 3.read.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Sun 13 Jun 2021 03:28:28 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\033[0;1;31mUsage: cmd filename\033[0m" "\n");
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(-1);
    } else {
        perror("open");
    }
    printf("fd = %d\n", fd);
    char buf[20];
    ssize_t n;
    n = read(fd, buf, 10);
    printf("read %ld bytes\n", n);
    for (int i = 0; i < n; i++) {
        printf("%c", buf[i]);
    }
    printf("\n");
    n = read(fd, buf, 10);
    printf("read %ld bytes\n", n);
    for (int i = 0; i < n; i++) {
        printf("%c", buf[i]);
    }
    printf("\n");
    close(fd);
    return 0;
}
