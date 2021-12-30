/*************************************************************************
	> File Name: 15.redirect.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 09:16:26 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main() {
    write(5, "hello\n", 6);
    return 0;
}
