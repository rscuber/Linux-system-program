/*************************************************************************
	> File Name: 14.getmsg.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Tue 06 Jul 2021 12:14:28 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGLEN 20

typedef struct msgbuf {
    long mtype;
    char mtext[MSGLEN];
} MSG;

int main() {
    key_t key = ftok("./11.test", 8);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    printf("key = %#x\n", key);
    int mqid = msgget(key, IPC_CREAT | 0666);
    printf("mqid = %d\n", mqid);
    MSG msg;
    msgrcv(mqid, &msg, MSGLEN, 2, 0);
    printf("msg.mtype = %ld\n", msg.mtype);
    printf("msg.mtext: %s\n", msg.mtext);
    msgrcv(mqid, &msg, MSGLEN, 1, 0);
    printf("msg.mtype = %ld\n", msg.mtype);
    printf("msg.mtext: %s\n", msg.mtext);
    return 0;
}
