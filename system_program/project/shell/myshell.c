/*************************************************************************
	> File Name: myshell.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Mon 20 Sep 2021 10:19:15 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>
#include "color.h"

#define MAX_LEN 100
#define hanle_error(msg) {\
    perror(msg);\
    exit(EXIT_FAILURE);\
}

void parse(char *buf, char *argv[MAX_LEN], int *argc) {
    int flag = 0;
    for (int i = 0; buf[i]; i++) {
        if (flag == 0 && !isspace(buf[i])) {
            argv[argc[0]++] = buf + i;
            flag = 1;
        } else if (isspace(buf[i])) {
            flag = 0;
            buf[i] = 0;
        }
    }
    argv[*argc] = NULL;
    return ;
}

int main(int argc, char *argv[]) {
    char *cmd[MAX_LEN], *new_cmd[MAX_LEN], *tips = BLUE_HL("-> ");
    int wstatus;
    while (1) {
        pid_t cpid = fork();
        if (cpid) {
            //父进程
            waitpid(cpid, &wstatus, 0);
            //因为exit退出状态的值是由8个bit位组成,所以 -1 -> 255；
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 255) {
                exit(EXIT_SUCCESS);
            }
        } else { //子进程
            while (1) {
                ssize_t n;
                char buf[MAX_LEN] = {0};
                //输出提示信息
                write(STDOUT_FILENO, tips, strlen(tips));

                //若输入换行(前面可能有空格)则继续,若输入exit则退出
                n = read(STDIN_FILENO, buf, MAX_LEN);
                if (n == -1) hanle_error("read from stdin");
                if (!strncmp(buf, "exit", 4)) exit(-1);
                //把exit放在前面,避免exit'\n'被当作"   \n"
                if (buf[strlen(buf)] == '\n') continue; 
                //execvp执行输入的命令
                int cnt = 0, fd1, fd2;
                parse(buf, cmd, &cnt);
                for (int i = 1; i < cnt; i++) {
                    switch (cmd[i][0]) {
                        case '<': {
                            fd1 = open(cmd[i + 1], O_RDONLY);
                            if (fd1 == -1) hanle_error("open fd1");
                            dup2(fd1, 0);
                        } break;
                        case '>': {
                            fd2 = open(cmd[i + 1], O_WRONLY | O_CREAT, 0644);
                            if (fd2 == -1) hanle_error("open fd2");
                            dup2(fd2, 1);
                        } break;
                        case '|': {
                            
                        } break;
                    }   
                }
                int j = 0;
                for (int i = 0; i < cnt; i++) {
                    if (cmd[i][0] == '<' || cmd[i][0] == '>') {
                        i++;
                    } else {
                        printf("strcpy(%s, %s)\n", new_cmd[j++], cmd[i]);
                        strcpy(new_cmd[j++], cmd[i]);
                    }
                }
                printf("new_cmd:");
                for (int i = 0; i < j; i++) {
                    printf("%s ", new_cmd[i]);
                }
                new_cmd[j] = NULL;
                if (execvp(new_cmd[0], new_cmd) == -1) {
                    hanle_error("execvp");
                }
            }
        }
    }
    return 0;
}
