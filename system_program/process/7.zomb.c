/*************************************************************************
	> File Name: 7.zomb.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 03 Jul 2021 05:31:30 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid) {
        while (1) sleep(1);
    } else {
        exit(3);
    }
    return 0;
}
