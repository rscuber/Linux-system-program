/*************************************************************************
	> File Name: 11.popenR.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 04 Jul 2021 11:43:18 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    FILE *fp = popen("cat ./11.test", "r");
    if (!fp) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    int c;
    while (~(c = getc(fp))) {
        putchar(toupper(c));
    }
    pclose(fp);
    return 0;
}
