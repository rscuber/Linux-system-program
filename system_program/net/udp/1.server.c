/*************************************************************************
	> File Name: 1.server.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 18 Jul 2021 12:19:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 6666
#define MAX_LEN 80
#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

int main() {
    struct sockaddr_in servaddr, cliaddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        handle_error("socket");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        handle_error("bind");
    }
    printf("udpserver ready~\n");

    while (1) {
        char buf[MAX_LEN], des[INET_ADDRSTRLEN];
        ssize_t n;
        socklen_t cliaddr_len = sizeof(cliaddr);
        n = recvfrom(
            sockfd, buf, MAX_LEN, 0, 
            (struct sockaddr *)&cliaddr, &cliaddr_len
        );
        if (n == -1) handle_error("recvfrom");
        printf("received from %s:%d\n", 
            inet_ntop(AF_INET, &cliaddr.sin_addr, des, sizeof(des)),
            ntohs(cliaddr.sin_port)
        );
        write(STDOUT_FILENO, buf, n);
        for (int i = 0; i < n; i++) {
            buf[i] = toupper(buf[i]);
        }
        n = sendto(
            sockfd, buf, n, 0, 
            (struct sockaddr *)&cliaddr, sizeof(cliaddr)
        );
        if (n == -1) handle_error("sendto");
    }
    close(sockfd);
    return 0;
}
