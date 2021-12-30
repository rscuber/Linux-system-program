/*************************************************************************
	> File Name: 12.sigchld.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 08 Jul 2021 07:31:26 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sig_child(int signo) {
    int wst;
    pid_t pid = wait(&wst);
    if (WIFEXITED(wst)) {
        printf("proc: %d exit with code %d\n", pid, WEXITSTATUS(wst));
    } else {
        printf("exit with other code %d\n", WEXITSTATUS(wst));
    }
    return ;
}

int main() {
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        printf("child 1 is %d\n", cpid);
        cpid = fork();
        if (cpid < 0) {
            perror("fork 2 child");
            exit(EXIT_FAILURE);
        }
        if (cpid) {
            printf("child 2 is %d\n", cpid);
            struct sigaction act, oact;
            act.sa_handler = sig_child;
            act.sa_flags = 0;
            sigemptyset(&act.sa_mask);
            sigaction(SIGCHLD, &act, &oact);
            int n = 10;
            while (n--) {
                printf("work ~\n");
                sleep(1);
            }
            sigaction(SIGCHLD, &oact, NULL);
        } else {
            //第2个子进程
            sleep(5);
            exit(5);
        }
    } else {
        //第1个子进程
        sleep(3);
        exit(3);
    }
    return 0;
}
