/*************************************************************************
	> File Name: 1.fork.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 10:26:45 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *msg;
    int n;
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(1);
    }
    if (cpid == 0) {
        n = 6;
        while (n--) {
            printf("child: self_id = %d\t parent_id = %d\n", getpid(), getppid());
            sleep(1);
        }
        printf("\033[0;1;31mchild end\n\033[0m");
    } else {
        n = 3;
        while (n--) {
            printf("parent: self_id = %d\t parent_id = %d\n", getpid(), getppid());
            sleep(1);
        }
        printf("\033[0;1;31mparent end\n\033[0m");
    }
    return 0;
}
