/*************************************************************************
	> File Name: 4.exec.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 06:49:24 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *arr[] = {"hello", "-a", "-l", NULL};
    execvp("ls", arr);
    #if 0
    execlp("ls", "ls", "-a", "-l", NULL); 
    //execlp("ls", "hahaha", "-a", "-l", NULL); ls 后的第一个参数"hahaha"其实是不看的
    #endif 
    perror("exec");
    exit(1);
    return 0;
}
