/*************************************************************************
	> File Name: 2.client.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 18 Jul 2021 01:04:05 PM CST
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


#define SERV_PROT 6666
#define MAX_LEN 80
#define handle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

int main() {
    struct sockaddr_in servaddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        handle_error("socket");
    }
    //ip地址:端口初始化
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PROT);;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    
    ssize_t n;
    char buf[MAX_LEN];
    while (n = read(STDIN_FILENO, buf, MAX_LEN)) {
        if (n == -1) handle_error("read");
        n = sendto(
            sockfd, buf, n, 0, 
            (struct sockaddr *)&servaddr, sizeof(servaddr)
        );
        if (n == -1) handle_error("sendto");
        n = recvfrom(sockfd, buf, n, 0, NULL, NULL);
        if (n == -1) handle_error("recvfrom");
        write(STDOUT_FILENO, buf, n);
    }
    close(sockfd);
    return 0;
}
