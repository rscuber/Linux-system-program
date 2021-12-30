/*************************************************************************
	> File Name: 4.read_stdin.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Sun 13 Jun 2021 03:57:12 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buf[20];
    ssize_t n;
    //n = read(0, buf, 10);
    while (1) {
        n = read(STDIN_FILENO, buf, 10);
        if (n < 0) {
            perror("RED STDIN");
            exit(-1);
        }
        if (n == 0) break;
        printf("read %ld bytes\n", n);
        for (int i = 0; i < n; i++) {
            printf("%c", buf[i]);
           
        }
        putchar(10);    //换行
    }
    return 0;
}
