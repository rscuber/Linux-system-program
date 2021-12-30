/*************************************************************************
	> File Name: 13.fcntl.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 11:22:23 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags < 0) {
        perror("fcntl get flags");
        exit(1);
    }
    flags |= O_NONBLOCK;
    flags = fcntl(STDIN_FILENO, F_SETFL, flags);
    if (flags < 0) {
        perror("fcntl set flags");
        exit(1);
    }
    char buf[10];
    ssize_t n;
    int cnt = 10;
    while (cnt--) {
        n = read(STDIN_FILENO, buf, 5);
        if (~n) {
            printf("read %ld bytes\n", n);
            write(STDOUT_FILENO, buf, n);
            write(1, "\n", 1);
            break;
        }
        if (errno != EAGAIN) {
            perror("read");
            exit(1);
        }
        write(STDOUT_FILENO, "try again?\n", 11);
        sleep(1);
    }
    return 0;
}
