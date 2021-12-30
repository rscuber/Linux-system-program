/*************************************************************************
	> File Name: client.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 01 Oct 2021 11:51:42 AM CST
 ************************************************************************/

#include "head.h"

#define MAX_LEN 1024
#define SERV_PORT 8080

#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

int main() {
    struct sockaddr_in servaddr; 
    char buf[MAX_LEN] = {0};
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) handle_error("socket");

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        handle_error("connect");
    }

    ssize_t n;
    while (n = read(STDIN_FILENO, buf, MAX_LEN)) {
        if (n < 0)  handle_error("read from stdin"); 
        if (write(sockfd, buf, n) < 0) {
            handle_error("write to sockfd");
        }
        n = read(sockfd, buf, MAX_LEN);
        if (n < 0) handle_error("read from sockfd");
        printf("responce from server:\n");
        if (write(STDOUT_FILENO, buf, n) < 0) {
            handle_error("write to stdout");
        }
    }
    close(sockfd);
    return 0;
}
