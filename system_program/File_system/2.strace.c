/*************************************************************************
	> File Name: 2.strace.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Tue 22 Jun 2021 09:42:22 PM CST
 ************************************************************************/

#include <stdio.h>

int main() {
    printf("hello world\n"); //strace ./a.out 查看程序执行过程中的系统调用
    return 0;
}
