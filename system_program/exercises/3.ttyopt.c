/*************************************************************************
	> File Name: 3.ttyopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 11 Jul 2021 11:49:28 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("fd %d: %s\n", 0, ttyname(0));
    printf("fd %d: %s\n", 1, ttyname(1));
    printf("fd %d: %s\n", 2, ttyname(2));
    return 0;
}
