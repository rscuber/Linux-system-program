/*************************************************************************
	> File Name: 2.killopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 04:19:00 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t cpid = fork();    
    if (cpid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        sleep(3);
        if (kill(cpid, SIGQUIT) < 0) {
            perror("kill");
            exit(EXIT_FAILURE);
        }
        int wst;
        wait(&wst);
        if (WIFSIGNALED(wst)) {
            printf("child process terminated by signal %d\n", WTERMSIG(wst));
        } else {
            printf("child process terminated by other ways\n");
        }
    } else {
        while (1) {
            printf("child sleep 1 sec\n");
            sleep(1);
        }
    }
    return 0;
}
