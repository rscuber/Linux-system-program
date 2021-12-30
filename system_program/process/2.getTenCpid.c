/*************************************************************************
	> File Name: 2.getTenCpid.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 11:50:45 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 10; i++) {
        pid_t cpid = fork();
        if (cpid < 0) {
            perror("fork");
            exit(1);
        }
        if (cpid == 0) {
            printf("child[%d]: self_id = %d\t parent_id = %d\n", 
                i, getpid(), getppid()
            );
            sleep(1);
            if (i == 9) printf("\033[0;1;31mchild end\n\033[0m");
            break;
        } else {
            if (i == 1) sleep(1);
            if (i == 9) printf("\033[0;1;31mparent end\n\033[0m");
        }
    }
    return 0;
}
