/*************************************************************************
	> File Name: 4.cond.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 11 Jul 2021 12:20:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct Goods {
    int data;
    struct Goods *next;
} Goods;

Goods *head = NULL;
pthread_mutex_t headLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t hasGoods = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    Goods *p;
    while (1) {
        p = (Goods *)malloc(sizeof(Goods)); 
        p->data = rand() % 100;
        //对头节点的操作和打印信息必须为原子操作
        pthread_mutex_lock(&headLock);
        p->next = head;
        head = p;
        printf("produce: %d\n", p->data);
        pthread_cond_broadcast(&hasGoods);  //pthread_cond_signal效果一样
        pthread_mutex_unlock(&headLock);
        sleep(rand() % 3);
    }
    return NULL;
}

void *consumer(void *arg) {
    Goods *c;
    while (1) {
        pthread_mutex_lock(&headLock);
        //应再判断一次,故用while(避免有信号,但是货物已经被其他线程消费了的情况)
        while (!head) {
            pthread_cond_wait(&hasGoods, &headLock);
        }
        c = head;
        head = head->next;
        printf("consume: %d\n", c->data);
        pthread_mutex_unlock(&headLock);
        free(c);
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t ptid, ctid1, ctid2, ctid3, ctid4;
    pthread_create(&ptid, NULL, producer, NULL);
    pthread_create(&ctid1, NULL, consumer, NULL);
    pthread_create(&ctid2, NULL, consumer, NULL);
    pthread_create(&ctid3, NULL, consumer, NULL);
    pthread_create(&ctid4, NULL, consumer, NULL);
    pthread_join(ptid, NULL);
    pthread_join(ctid1, NULL);
    pthread_join(ctid2, NULL);
    pthread_join(ctid3, NULL);
    pthread_join(ctid4, NULL);
    return 0;
}
