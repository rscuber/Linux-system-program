/*************************************************************************
	> File Name: 8.waitpid.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 03 Jul 2021 06:49:34 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        int n = 10;
        while (n--) {
            printf("this is child process %d\n", getpid());
            sleep(1);
        }
        exit(3);
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val)) {
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        } else if (WIFSIGNALED(stat_val)) {
            printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
        }
    }
    return 0;
}
