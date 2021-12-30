/*************************************************************************
	> File Name: 10.calBytes.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 16 Jun 2021 11:17:01 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("open file");
        exit(1);
    }
    rewind(fp);
    fseek(fp, 0, SEEK_END);
    printf("bytes = %ld\n", ftell(fp));
    fclose(fp);
    return 0;
}
