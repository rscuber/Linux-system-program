/*************************************************************************
	> File Name: 14.sendmsg.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Mon 05 Jul 2021 11:31:12 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

#define MSGLEN 20

typedef struct msgbuf {
    long mtype;     //必须>1
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
    if (mqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("mqid = %d\n", mqid);
    MSG msg;    
    msg.mtype = 1;
    strncpy(msg.mtext, "hi, how are you?\n", MSGLEN);
    msgsnd(mqid, &msg, MSGLEN, 0);
    msg.mtype = 2;
    strncpy(msg.mtext, "godOfRang: online\n", MSGLEN);
    msgsnd(mqid, &msg, MSGLEN, 0);
    return 0;
}
