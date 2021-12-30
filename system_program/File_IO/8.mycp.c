/*************************************************************************
	> File Name: 8.mycp.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 16 Jun 2021 10:04:21 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void file_copy(FILE *fp1, FILE *fp2) {
    char c;
    while (~(c = fgetc(fp1))) {
        fputc(c, fp2);
    }
    return ;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("\033[0;1;31mUsage: cmd srcfile tagfile2\n\033[0m");
        exit(1);
    }
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "w");
    if (!fp1 || !fp2) {
        perror("open");
        exit(1);
    }
    file_copy(fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
