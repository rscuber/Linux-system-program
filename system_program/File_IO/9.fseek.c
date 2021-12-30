/*************************************************************************
	> File Name: 9.fseek.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 16 Jun 2021 11:02:31 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("./hello.txt", "r+");
    if (!fp) {
        perror("open file");
        exit(1);
    }
    fputc('A', fp);
    fputc('B', fp);
    fputc('C', fp);
    printf("pos = %ld\n", ftell(fp));
    fseek(fp, -3, SEEK_END);
    printf("pos = %ld\n", ftell(fp));
    fputc('X', fp);
    fputc('Y', fp);
    fclose(fp);
    return 0;
}
