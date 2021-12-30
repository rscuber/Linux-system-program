/*************************************************************************
	> File Name: server.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 30 Sep 2021 12:07:59 PM CST
 ************************************************************************/
#include "head.h"
#include "thread_pool/thread_pool.h"

#define MAXUSER    1024
#define MAXEVENTS  5
#define MAXTHREADS 4
#define BUF_SIZE   4096

#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

char *data[MAXUSER];
pthread_mutex_t mutex[MAXUSER];
int fd[MAXUSER], epollfd;

int socket_create(int port) {
    struct sockaddr_in servaddr;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    //服务端 ip地址:端口初始化
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(port);
    servaddr.sin_addr.s_addr = ntohl(INADDR_ANY);
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        handle_error("bind");
    }
    //是listenfd成为监听描述符
    if (listen(listenfd, 2) < 0) {
        handle_error("listen");
    } 
    return listenfd;
}

int accept_client(int listenfd) {
    int sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len = sizeof(cliaddr);
    if ((sockfd = 
        accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len)) < 0) {
        handle_error("accept");
    }
    char des[INET_ADDRSTRLEN];
    DBG(
        BOLD_GREEN "<DBG>" NONE "received from %s:%d\n", 
        inet_ntop(AF_INET, &cliaddr.sin_addr, des, sizeof(des)),
        ntohs(cliaddr.sin_port)
    );
    return sockfd;
}

int main(int argc, char *argv[]) {
    int opt, port;
    int server_listen, sockfd;
    //获取端口号
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p': {
                port = atoi(optarg); 
            } break;
                break;
            default: {
                fprintf(stderr, "Usage: %s -p port\n", argv[0]);
                exit(EXIT_FAILURE);
            }  
        }
    }

    if ((server_listen = socket_create(port)) < 0) {
        handle_error("socket_create");
    }
    DBG(BOLD_GREEN"<DBG>"NONE"Accepting connections...\n");

    if ((epollfd = epoll_create(1)) < 0) {
        handle_error("epoll_create");
    }

    for (int i = 0; i < MAXUSER; i++) {
        pthread_mutex_init(mutex + i, NULL);
    }

    task_queue *taskQueue = task_queue_init();
    pthread_t *tid = (pthread_t *)calloc(MAXTHREADS, sizeof(pthread_t));
    for (int i = 0; i < MAXTHREADS; i++) {
        pthread_create(tid + i, NULL, thread_run, (void *)taskQueue);
    }

    struct epoll_event ev, events[MAXEVENTS];
    ev.data.fd = server_listen;
    ev.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev) < 0) {
        handle_error("epoll_ctl");
    }

    for (;;) {
        int nfds = epoll_wait(epollfd, events, MAXEVENTS, -1);
        if (nfds < 0) handle_error("epoll_wait");
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_listen 
                && (events[i].events & EPOLLIN)
                ) {
                int sockfd = accept_client(server_listen);
                fd[sockfd] = sockfd;
                data[sockfd] = (char *)calloc(BUF_SIZE, sizeof(char));
                ev.data.fd = sockfd;
                ev.events = EPOLLIN | EPOLLET;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
                    handle_error("epoll_ctl");
                }
            } else if (events[i].events & EPOLLIN) {
                int clifd = events[i].data.fd;
                if (clifd < 3) continue;
                task_queue_push(taskQueue, clifd);
            }
        }
    }
    task_queue_clear(taskQueue);
    return 0;
}
