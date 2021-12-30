/*************************************************************************
	> File Name: 6.sigMask.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 09:36:36 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t set, oset;
    if (sigemptyset(&set) == -1) {
        perror("sigemptyset");
        exit(EXIT_FAILURE);
    }
    if (sigaddset(&set, SIGINT) == -1) {
        perror("sigaddset");
        exit(EXIT_FAILURE);
    }
    sigaddset(&set, SIGSEGV);
    if (sigprocmask(SIG_BLOCK, &set, &oset) == -1) {
        perror("sigprocmask block");
        exit(EXIT_FAILURE);
    }
    //raise(SIGSEGV);
    int n = 10;
    while (n--) {
        printf("sleep 1 sec\n");
        sleep(1);
    }
    if (sigprocmask(SIG_SETMASK, &oset, NULL) == -1) {
        perror("sigprocmask setmask");
        exit(EXIT_FAILURE);
    }
    while (n--) {
        printf("sleep 1 sec again\n");
        sleep(1);
    }
    return 0;
}
