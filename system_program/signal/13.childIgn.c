/*************************************************************************
	> File Name: 13.childIgn.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 08 Jul 2021 08:19:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t cpid = fork();
    if (cpid == -1) {
        perror("fork"); 
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        printf("child pid is %d\n", cpid); 
        struct sigaction act, oact;
        if (oact.sa_handler == SIG_IGN) {
            printf("old handler is ign\n");
        } else {
            printf("SIG_IGN: %p\n", SIG_IGN);
            printf("old handler is %p\n", oact.sa_handler);
        }
        //在Linux上可以自动清理终止的子进程, 不会产生僵尸进程
        act.sa_handler = SIG_IGN;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD, &act, &oact);
        int n = 10;
        while (n--) {
            printf("work ~\n");
            sleep(1);
        }
    } else {
        sleep(3);
        exit(3);
    }
    return 0;
}
