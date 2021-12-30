/*************************************************************************
	> File Name: thread_pool.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 30 Sep 2021 12:31:26 PM CST
 ************************************************************************/

#include "../head.h"
#include "thread_pool.h"

extern char *data[1024];
extern int epollfd;
extern pthread_mutex_t mutex[1024];

task_queue *task_queue_init() {
    task_queue *taskQueue = (task_queue *)malloc(sizeof(task_queue));
    taskQueue->head = NULL;
    taskQueue->tail = NULL;
    pthread_mutex_init(&taskQueue->lock, NULL);
    pthread_cond_init(&taskQueue->havetask, NULL);
    return taskQueue;
}

void task_queue_push(struct task_queue *taskQueue, int fd) {
    pthread_mutex_lock(&taskQueue->lock); 
    task *t = (task *)malloc(sizeof(task));
    t->fd = fd;
    t->next = NULL;
    if (taskQueue->tail) {
        taskQueue->tail->next = t;
        taskQueue->tail = t;
    } else {
        taskQueue->head = taskQueue->tail = t;
    }
    DBG(BOLD_GREEN "<DBG>" NONE "<Push> : %d\n", fd);
    pthread_cond_signal(&taskQueue->havetask);
    pthread_mutex_unlock(&taskQueue->lock);
    return ;
}

int task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->lock);
    while (taskQueue->head == NULL) {
        DBG(BOLD_GREEN "<DBG>" NONE "taskQueue is empty!\n");
        pthread_cond_wait(&taskQueue->havetask, &taskQueue->lock);
    }
    int fd = taskQueue->head->fd;
    task *temp = taskQueue->head;
    taskQueue->head = temp->next;
    if (taskQueue->head == NULL) taskQueue->tail = NULL;
    free(temp);
    DBG(BOLD_GREEN "<DBG>" NONE "<Pop> : %d\n", fd);
    pthread_mutex_unlock(&taskQueue->lock);
    return fd;
}

void task_queue_clear(task_queue *taskQueue) {
    if (taskQueue == NULL) return ;
    pthread_mutex_lock(&taskQueue->lock);
    task *p = taskQueue->head, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    pthread_mutex_unlock(&taskQueue->lock); 
    pthread_mutex_destroy(&taskQueue->lock);
    pthread_cond_destroy(&taskQueue->havetask);
    free(taskQueue);
    return ;
}

void do_echo(int sockfd) {
    char buffer[4096] = {0};
    int len = strlen(data[sockfd]);
    int nrecv;
    //接收数据
    if ((nrecv = recv(sockfd, buffer, sizeof(buffer), 0)) < 0) {
        epoll_ctl(epollfd, EPOLL_CTL_DEL, sockfd, NULL);
        close(sockfd);
        return ;
    }
    pthread_mutex_lock(&mutex[sockfd]);
    //数据转换
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
            data[sockfd][len++] = buffer[i] + 32;
        } else if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            data[sockfd][len++] = buffer[i] - 32;
        } else {
            data[sockfd][len++] = buffer[i];
            //判断是否出现回车
            //发送或者不发送
            if (buffer[i] == '\n') {
                send(sockfd, data[sockfd], len, 0);
                memset(data[sockfd], 0, 4096);
            }
        }
    }
    pthread_mutex_unlock(&mutex[sockfd]);
    return ;
}

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
    task_queue *taskQueue = (task_queue *)arg;
    while (1) {
        int fd = task_queue_pop(taskQueue);
        do_echo(fd);
    }
    return NULL;
}
