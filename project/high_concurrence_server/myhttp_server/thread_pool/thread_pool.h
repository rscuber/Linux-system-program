/*************************************************************************
	> File Name: thread_pool.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 30 Sep 2021 12:31:31 PM CST
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

typedef struct task {
    int fd;
    struct task *next;
} task;

typedef struct task_queue {
    struct task *head;
    struct task *tail;
    pthread_mutex_t lock;
    pthread_cond_t havetask;
} task_queue;

task_queue *task_queue_init();
void task_queue_push(task_queue *taskQueue, int fd);
int task_queue_pop(task_queue *taskQueue);
void task_queue_clear(task_queue *taskQueue);
void do_echo(int sockfd);
void *thread_run(void *arg);

#endif
