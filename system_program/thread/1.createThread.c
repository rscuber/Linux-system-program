/*************************************************************************
	> File Name: 1.createThread.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 09 Jul 2021 12:28:07 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_t ptid;

void printid(char *);

void *tfunc(void *arg) {
    printid(arg);
    printf("%s\t\tptid: %lu (%p)\n", (char *)arg, ptid, ptid);
    return NULL;
}
 
void printid(char *tip) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s  pid: %u tid: %lu (%p)\n", tip, pid, tid, tid);
    return ;
}

int main() {
    int eno = pthread_create(&ptid, NULL, tfunc, "new  thread");
    if (eno) {
        printf("create thread error: %s\n", strerror(eno));
        exit(EXIT_FAILURE);
    }
    pthread_join(ptid, NULL);//等待新线程结束
    printid("main thread");
    return 0;
}
