/*************************************************************************
	> File Name: 7.mycat.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Wed 16 Jun 2021 09:22:41 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\033[0;1;31mUsage: cmd filename\n\033[0m");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            perror("open file");
            exit(1);
        }
        char c; 
        while ((c = fgetc(fp)) != EOF) {  //while (~(c = (fgetc(fp))))
            printf("%c", c);
        }
        fclose(fp);
    }
    return 0;
}
