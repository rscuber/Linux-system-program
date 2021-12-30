/*************************************************************************
	> File Name: 16.ioctl.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 09:42:59 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    struct winsize size;
    if (!isatty(1)) {
        printf("1 is not a tty\n");
        exit(1);
    }
    if (ioctl(1, TIOCGWINSZ, &size) < 0) {
        perror("ioctl");
        exit(1);
    }
    printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
    return 0;
}
