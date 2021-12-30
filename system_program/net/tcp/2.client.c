/*************************************************************************
	> File Name: 2.client.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 17 Jul 2021 06:14:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERV_PORT 6666 
#define MAX_LEN 80
#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

int main() {
    struct sockaddr_in servaddr;
    char buf[MAX_LEN] = {0};

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        handle_error("socket");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        handle_error("connect");
    }

    ssize_t n;
    while ((n = read(STDIN_FILENO, buf, MAX_LEN))) {
        if (n == -1) handle_error("read from stdin");
        if (write(sockfd, buf, n) == -1) {
            handle_error("write to sockfd");
        }
        if (!strncmp(buf, "quit", 4)) {
            printf("Connection to tcpServer closed.\n");
            break;
        }

        n = read(sockfd, buf, MAX_LEN);
        if (n == -1) {
            handle_error("read from sockfd");
        }
        printf("response from server:\n");
        if (write(STDOUT_FILENO, buf, n) == -1) {
            handle_error("write to stdout");
        }
    }
    close(sockfd);
    return 0;
}
