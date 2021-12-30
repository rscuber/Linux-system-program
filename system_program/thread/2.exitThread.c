/*************************************************************************
	> File Name: 2.exitThread.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 09 Jul 2021 12:01:36 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *tfunc1(void *arg) {
    printf("thread 1 is returning\n");
    return NULL;
}

void *tfunc2(void *arg) {
    printf("thread 2 is exiting\n");
    pthread_exit((void *)2);
    return NULL;
}

void *tfunc3(void *arg) {
    while (1) {
        printf("thread 3 is sleeping\n");
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t tid;
    void *sts;
    pthread_create(&tid, NULL, tfunc1, NULL);
    pthread_join(tid, &sts);
    printf("thread 1 exit with code %ld\n", (long)sts);

    pthread_create(&tid, NULL, tfunc2, NULL);
    pthread_join(tid, &sts);
    printf("thread 2 exit with code %ld\n", (long)sts);

    pthread_create(&tid, NULL, tfunc3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &sts);
    printf("thread 3 exit with code %ld\n", (long)sts);
    return 0;
}
