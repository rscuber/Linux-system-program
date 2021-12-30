/*************************************************************************
	> File Name: 12.readfifo.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 04 Jul 2021 04:29:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char buf[20];
    int fd = open("./tube", O_RDONLY);
    if (fd < 0) {
        perror("open tube");
        exit(EXIT_FAILURE);
    }
    ssize_t n = read(fd, buf, 20);
    if (n < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    printf("read %ld types\n", n);
    write(STDOUT_FILENO, buf, n);
    close(fd);
    return 0;
}
