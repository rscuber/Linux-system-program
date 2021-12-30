/*************************************************************************
	> File Name: 3.add.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 09 Jul 2021 11:34:33 PM CST
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

int cnt = 0;
pthread_mutex_t add_lock = PTHREAD_MUTEX_INITIALIZER;

void *add(void *arg) {
    int val;
    for (int i = 0; i < 5000; i++) {
        //保证原子性
        pthread_mutex_lock(&add_lock);
        val = cnt;
        printf("%p: %d\n", (void *)pthread_self(), val);
        cnt = val + 1;
        pthread_mutex_unlock(&add_lock);
    }
    return NULL;
}

int main() {
    pthread_t tida, tidb;
    pthread_create(&tida, NULL, add, NULL);
    pthread_create(&tidb, NULL, add, NULL);
    pthread_join(tida, NULL);
    pthread_join(tidb, NULL);
    return 0;
}
