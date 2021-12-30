/*************************************************************************
	> File Name: 1.buffer.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Sat 12 Jun 2021 04:23:56 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("%d\n", STDIN_FILENO);
    printf("%d\n", STDOUT_FILENO);
    printf("%d\n", STDERR_FILENO);
    return 0;
    //fputc('A', stdout);     //stdout 行缓冲
    //fputc('B', stdout);
    //fputc('\n', stdout);
    //fputc('A', stderr);       //stderr 无缓冲
    for (int i = 0; i < 1025; i++) {
        fputc('A', stdout);     //写满缓冲区
    }
    while (1) {
        ;
    } 
    return 0;
}
