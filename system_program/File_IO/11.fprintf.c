/*************************************************************************
	> File Name: 11.fprintf.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 10:05:20 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r+");
    if (!fp) {
        perror("fopen");
        exit(1);
    }
    int a = 123;
    fprintf(stdout, "print %d to %s success!\n", a, argv[1]);
    fprintf(fp, "a = %d\n", a);
    char buf[20];
    sprintf(buf, "a = %d\n", a);
    printf("%s", buf);
    fclose(fp);
    return 0;
}
