/*************************************************************************
	> File Name: 4.daemon.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Mon 12 Jul 2021 08:49:55 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        exit(0);
    } 
    pid_t sid = setsid();
    printf("new session id is %d\n", sid);
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
    while (1) sleep(1);
    return 0;
}
