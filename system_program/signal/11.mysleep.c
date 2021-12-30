/*************************************************************************
	> File Name: 11.mysleep.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 08 Jul 2021 06:13:45 PM CST
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_alarm(int signo) {
    return ;
}

unsigned int mysleep(unsigned int sec) {
    sigset_t set, oset, susmask;
    struct sigaction act, oact;
    //阻塞SIGALRM信号
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigprocmask(SIG_BLOCK, &set, &oset);

    //替换SIGALRM的信号处理函数
    act.sa_handler = sig_alarm;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask); 
    sigaction(SIGALRM, &act, &oact);

    //开启alarm
    alarm(sec);

    //获取老的信号屏蔽字
    susmask = oset;

    //删除SIGALRM信号的阻塞(不管是否存在), 使其畅通
    sigdelset(&susmask, SIGALRM);
    
    //临时设置信号屏蔽字为susmask, 并挂起程序, 等待信号到来
    sigsuspend(&susmask);
    perror("sigsuspend"); 

    //获取剩余睡眠时间
    unsigned int unslept = alarm(0);

    //先恢复信号处理动作, 再恢复信号屏蔽字
    sigaction(SIGALRM, &oact, NULL);
    sigprocmask(SIG_SETMASK, &oset, NULL);
    return unslept;
}

int main() {
    int n = 10;
    while (n--) {
        printf("mysleep 1 sec\n");
        mysleep(1);
    }
    return 0;
}
