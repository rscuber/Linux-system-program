/*************************************************************************
	> File Name: 9.pipe.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 03 Jul 2021 08:04:08 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buf[20];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid > 0) {
        close(fd[0]);
        write(fd[1], "hello pipe\n", 11);
        wait(NULL);
    } else {
        close(fd[1]);
        write(STDOUT_FILENO, "child sleep 1s\n", 15);
        sleep(1);
        ssize_t n = read(fd[0], buf, 20);
        write(STDOUT_FILENO, buf, n);
    }
    return 0;
}
