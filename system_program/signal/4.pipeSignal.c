/*************************************************************************
	> File Name: 4.pipeSignal.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 05:32:37 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pfd[2];
    if (pipe(pfd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        close(pfd[0]);
        close(pfd[1]);
        int wst;
        wait(&wst);
        if (WIFSIGNALED(wst)) {
            printf("exit with signal %d\n", WTERMSIG(wst));
        } else {
            printf("exit with other ways");
        }
    } else {
        sleep(3);
        close(pfd[0]);
        write(pfd[1], "hello\n", 6);
        sleep(3);
    }
    return 0;
}
