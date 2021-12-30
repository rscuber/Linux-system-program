/*************************************************************************
	> File Name: 5.write.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Sun 13 Jun 2021 04:27:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buf[20];
    ssize_t n;
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        perror("READ STDIN");
        exit(-1);
    }
    printf("read %ld bytes\n", n);
    write(STDOUT_FILENO, buf, n);
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}
