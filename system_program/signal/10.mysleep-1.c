/*************************************************************************
	> File Name: 10.mysleep.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 08 Jul 2021 11:45:26 AM CST
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_alarm(int signo) {
    return ;
}

unsigned int mysleep(unsigned int sec) {
    if (!sec) return 0;
    struct sigaction act, oact;
    //act.sa_handler = SIG_DFL;     直接中断
    //act.sa_handler = SIG_IGN;     挂起阻塞(忽略信号)
    act.sa_handler = sig_alarm;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, &oact);
    alarm(sec);
    pause();
    unsigned int unslept = alarm(0);
    sigaction(SIGALRM, &oact, NULL);
    return unslept;
}

int main() {
    int n = 5;
    while (n--) {
        printf("hello mysleep 1 sec\n");
        mysleep(1);
    }
    return 0;
}
