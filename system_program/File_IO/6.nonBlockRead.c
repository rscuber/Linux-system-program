/*************************************************************************
	> File Name: 6.nonBlockRead.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 16 Jun 2021 01:43:06 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("OPEN /dev/tty");
        exit(-1);
    } 
    char buf[10];
    ssize_t n;
    int cnt = 10;
    while (cnt--) {
        n = read(fd, buf, 10);
        if (~n) {
            printf("read %ld bytes\n", n);
            write(STDOUT_FILENO, buf, n);
            break;
        }
        if (errno != EAGAIN) {
            perror("READ /dev/tty");
            exit(-1);
        }
        write(STDOUT_FILENO, "try try?\n", 9);
        sleep(1);
    }
    close(fd);
    return 0;
}
