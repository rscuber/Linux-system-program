/*************************************************************************
	> File Name: 12.writefifo.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 04 Jul 2021 04:34:31 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("./tube", O_WRONLY);
    if (fd < 0) {
        perror("open tube");
        exit(EXIT_FAILURE);
    }
    ssize_t n = write(fd, "hello FIFO\n", 11);
    if (n < 0) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}
