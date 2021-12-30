/*************************************************************************
	> File Name: mypwd.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Mon 21 Jun 2021 10:24:22 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[], char *env[]) {
    #if 0
    for (int i = 0; env[i]; i++) {
        printf("env[%d]: %s\n", i, env[i]);
    }
    #endif
    printf("%s\n", env[16] + 4);
    return 0;
}
