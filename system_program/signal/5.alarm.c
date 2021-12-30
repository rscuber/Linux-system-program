/*************************************************************************
	> File Name: 5.alarm.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 06:05:40 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

int main() {
    alarm(5);
    sleep(3);
    unsigned int left = alarm(1);
    printf("left = %d\n", left);
    while (1);
    int8_t i;
    for (i = 0; i > -1; i++) {} //不是死循环
    printf("i = %" PRId8 "\n", i);
    return 0;
}
