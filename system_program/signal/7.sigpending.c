/*************************************************************************
	> File Name: 7.sigpending.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 11:14:08 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void print_sig(const sigset_t *set) {
    for (int i = 1; i <= 31; i++) {
        sigismember(set, i) ? putchar('1') : putchar('0');
    }
    putchar(10);
    return ;
}

int main() {
    sigset_t set, oset, pset;
    if (sigemptyset(&set) == -1) {
        perror("sigemptyset");
        exit(EXIT_FAILURE);
    }
    if (sigaddset(&set, SIGINT)) {
        perror("sigaddset SIGINT");
        exit(EXIT_FAILURE);
    }
    if (sigaddset(&set, SIGQUIT)) {
        perror("sigaddset SIGQUIT");
        exit(EXIT_FAILURE);
    }
    if (sigprocmask(SIG_BLOCK, &set, &oset) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
    int n = 30;
    while (n--) {
        if (sigpending(&pset) == -1) {
            perror("sigpending");
            exit(EXIT_FAILURE);
        }
        print_sig(&pset);
        sleep(1);
    }
    sigprocmask(SIG_SETMASK, &oset, NULL);
    return 0;
}
