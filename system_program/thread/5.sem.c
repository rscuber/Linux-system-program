/*************************************************************************
	> File Name: 5.sem.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 11 Jul 2021 06:04:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5

int q[NUM], head, tail;
sem_t blankNum, goodsNum;

void *producer(void *arg) {
    while (1) {
        sem_wait(&blankNum);
        q[head] = rand() % 100 + 1;
        printf("producer: %d\n", q[head]);
        head = (head + 1) % NUM;
        sem_post(&goodsNum);
        sleep(rand() % 3);
    }
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&goodsNum);
        printf("consumer: %d\n", q[tail]);
        q[tail] = 0;
        tail = (tail + 1) % NUM;
        sem_post(&blankNum);
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    srand(time(NULL)); 
    pthread_t ptid, ctid1, ctid2, ctid3;
    sem_init(&blankNum, 0, NUM);
    sem_init(&goodsNum, 0, 0);
    pthread_create(&ptid, NULL, producer, NULL);
    pthread_create(&ctid1, NULL, consumer, NULL);
    pthread_create(&ctid2, NULL, consumer, NULL);
    pthread_create(&ctid3, NULL, consumer, NULL);
    pthread_join(ptid, NULL);
    pthread_join(ctid1, NULL);
    pthread_join(ctid2, NULL);
    pthread_join(ctid3, NULL);
    sem_destroy(&blankNum);
    sem_destroy(&goodsNum);
    return 0;
}
