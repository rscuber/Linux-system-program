/*************************************************************************
	> File Name: 1.kill.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 04:13:10 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    if (kill(10154, SIGSEGV) < 0) {     //ps -u查看pid
        perror("kill");
        exit(EXIT_FAILURE);
    }
    return 0;
}
