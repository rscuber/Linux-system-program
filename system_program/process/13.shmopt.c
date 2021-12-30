/*************************************************************************
	> File Name: 13.shmopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 04 Jul 2021 07:58:49 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <strings.h>

int main() {
    key_t key = ftok("./11.test", 9);
    if (key < 0) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("key = 0x%x\n", key);
    int shmid = shmget(key, 20, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("shmid = %d\n", shmid);
    char *shmp = shmat(shmid, NULL, 0);
    if (shmp < 0) {
        perror("shmat");
        exit(EXIT_FAILURE); 
    } 
    printf("shmp = %p\n", shmp);
    //snprintf(shmp, 20, "hello\n");
    //printf("shmp: %s", shmp);
    bzero(shmp, 20);
    pid_t cpid = fork();
    if (cpid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid) {
        //parent process
        while (1) {
            scanf("%[^\n]s", shmp);
            if (!strcmp(shmp, "quit")) {
                break;
            }
        }
        wait(NULL);
    } else {
        //child process
        while (1) {
            if (!strcmp(shmp, "quti")) {
                break;
            }
            if (*shmp) {
                printf("child read %s\n", shmp);
                bzero(shmp, 20);
            }
            sleep(1);
        }
    }
    shmdt(shmp);
    return 0;
}
