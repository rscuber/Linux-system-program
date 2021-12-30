/*************************************************************************
	> File Name: 10.specialPipes.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 03 Jul 2021 09:36:02 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    char buf[20];
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid > 0) {
        sleep(1);
        close(fd[0]);
        write(fd[1], "hello\n", 6);
        close(fd[1]);
        wait(NULL);
    } else {
        close(fd[1]);
        close(fd[0]);
        /*
        ssize_t n = read(fd[0], buf, 6);
        printf("read %ld types\n", n);
        write(STDOUT_FILENO, buf, n);
        n = read(fd[0], buf, 5);
        printf("read %ld types\n", n);
        write(STDOUT_FILENO, buf, n);
        */
    }

    return 0;
}
