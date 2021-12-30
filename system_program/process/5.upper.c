/*************************************************************************
	> File Name: 5.upper.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 11:08:06 PM CST
 ************************************************************************/

#include <stdio.h>
#include <ctype.h>

int main() {
    int ch;
    while (~(ch = getchar())) {
        putchar(toupper(ch));
    }
    return 0;
}
