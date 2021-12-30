/*************************************************************************
	> File Name: 8.sigHandler.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 08 Jul 2021 10:15:55 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void undead(int signo) {
    printf("get signo = %d, I'm alive~\n", signo);
    return ;
}

int main() {
    struct sigaction act, oact;
    act.sa_handler = undead;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGINT, &act, &oact) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    int n = 10;
    while (n--) {
        printf("sleep 1 sec\n");
        sleep(1);
    }
    if (~sigaction(SIGINT, &oact, NULL)) {
        printf("recover, end\n");
    } else {
        perror("sigaction recover");
        exit(EXIT_FAILURE);
    }
    return 0;
}
