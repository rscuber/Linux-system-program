/*************************************************************************
	> File Name: 1.server.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 17 Jul 2021 05:15:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/epoll.h>

#define SERV_PORT 6666
#define MAX_LEN 80
#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

typedef struct Task {
    int fd;
    struct Task *next;
} Task;

typedef struct Task_queue {
    Task *head, *tail;
    pthread_mutex_t lock;
    pthread_cond_t havetask;
} Task_queue;

Task_queue *task_queue_init() {
    Task_queue *temp = (Task_queue *)malloc(sizeof(Task_queue));
    temp->head = NULL;
    temp->tail = NULL;
    pthread_mutex_init(&temp->lock, NULL); 
    pthread_cond_init(&temp->havetask, NULL);
    return temp;
}

void task_queue_push(Task_queue *tp, int fd) {
    pthread_mutex_lock(&tp->lock);
    Task *temp = (Task *)malloc(sizeof(Task));
    temp->fd = fd;
    temp->next = NULL;
    if (!tp->tail) {
        tp->head = tp->tail = temp; 
    } else {
        tp->tail->next = temp;
        tp->tail = temp;
    }
    pthread_cond_broadcast(&tp->havetask);
    pthread_mutex_unlock(&tp->lock);
    return ;
}

Task task_queue_pop(Task_queue *tp) {
    pthread_mutex_lock(&tp->lock);
    while (tp->head == NULL) {
        //用while原因: 当次线程扔出锁后，被其他消费者线程抢到也执行到了这一行，
        //然后再抛出锁, 被生产者抢到后才会生产任务
        //会导致其他消费者线程产生有任务的假象
        pthread_cond_wait(&tp->havetask, &tp->lock);
    }
    Task temp, *k;  //temp 在栈里
    k = tp->head;
    temp = *k;
    tp->head = tp->head->next;
    if (!tp->head) tp->tail = NULL;
    free(k);
    pthread_mutex_unlock(&tp->lock);
    return temp;
}

void task_queue_free(Task_queue *tp) {
    pthread_mutex_lock(&tp->lock);
    Task *p = tp->head, *q; 
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    pthread_mutex_unlock(&tp->lock);
    pthread_mutex_destroy(&tp->lock);
    pthread_cond_destroy(&tp->havetask);
    free(tp);
    return ;
}


typedef struct Tpid {
    Task_queue *tp;
    int id;
} Tpid;

void *up_server(void *arg) {
    pthread_detach(pthread_self());
    char buf[MAX_LEN];
    ssize_t n;
    Task_queue *tp = ((Tpid *)arg)->tp;
    int id = ((Tpid *)arg)->id;
    while (1) {
        Task temp = task_queue_pop(tp);
        int connfd = temp.fd;
        printf("thread[%d] get task fd = %d\n", id, connfd);
        n = read(connfd, buf, MAX_LEN);
        if (n == -1) {
            handle_error("read");
        }
        write(STDOUT_FILENO, buf, n);
        if (!strncmp(buf, "quit", 4)) {
            printf("thread[%d] finish task fd = %d\n", id, connfd);
            close(connfd);
            continue;
        }
        for (int i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }
        write(connfd, buf, n);
        printf("thread[%d] finish task fd = %d\n", id, connfd);
    }
    return NULL;
}


int main() {
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;

    Task_queue *tp = task_queue_init();
    
    //多线程
    pthread_t tid;
    Tpid arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i].tp = tp;
        arr[i].id = i + 1;
        pthread_create(&tid, NULL, up_server, arr + i);
        printf("thread[%d] tid is %#lx\n", i + 1, tid);
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        handle_error("socket");
    }

    int epfd = epoll_create(256);
    struct epoll_event ev, events[256];
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listenfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    //服务器 ip地址:端口初始化
    bzero(&servaddr, sizeof(servaddr)); //先清空
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY表示0.0.0.0

    //绑定服务器地址端口
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        handle_error("bind");
    }

    //使listenfd成为一个监听描述符
    if (listen(listenfd, 2) == -1) {
        handle_error("listen");
    }
    
    printf("Accepting connections...\n");
    while (1) {
        int nfds = epoll_wait(epfd, events, 256, -1);
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == listenfd) {
                cliaddr_len = sizeof(cliaddr_len); 
                //阻塞等待客户端连接
                connfd = accept(
                    listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len
                );
                if (connfd == -1) {
                    handle_error("accept");
                }
                char des[INET_ADDRSTRLEN]; //INET_ADDRSTRLEN=16
                printf(
                    "received from %s:%d\n", 
                    inet_ntop(AF_INET, &cliaddr.sin_addr, des, sizeof(des)), 
                    ntohs(cliaddr.sin_port)
                );
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            } else if (events[i].events & EPOLLIN) {
                int clifd = events[i].data.fd;
                if (clifd < 3) continue;
                task_queue_push(tp, clifd);
            } 
        }
        /*
        //父进程: 等待创建连接
        pid_t cpid = fork();
        if (cpid == -1) {
            handle_error("fork");
        }
        if (cpid > 0) {
            close(connfd);
            while (waitpid(-1, NULL, WNOHANG) > 0) {}
            continue;
        }
        close(listenfd);
        */
    } 
    task_queue_free(tp);
    return 0;
}
