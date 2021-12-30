/*************************************************************************
	> File Name: 11.popenW.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 04 Jul 2021 11:48:36 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("./upper", "w");
    if (!fp) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "hello world\n***godofrang***\n");
    pclose(fp);
    return 0;
}
