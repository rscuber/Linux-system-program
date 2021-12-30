/*************************************************************************
	> File Name: 1.getopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 03 Sep 2021 04:47:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ab:c::")) != -1) {
        switch (opt) {
            case 'a': {
                printf("opt a found\n");
                printf("optind = %d\n", optind);
            } break;
            case 'b': {
                printf("opt b found\n");
                printf("optind = %d\n", optind);
                printf("arg for b is %s\n", optarg);
            } break;
            case 'c': {
                printf("opt c found\n");
                printf("optind = %d\n", optind);
                printf("arg for c is %s\n", optarg);
            } break;
            default:{
                fprintf(stderr, "Usage: %s -a -b barg -c[carg]\n", argv[0]);
                exit(1);
            }
        }
    }
    return 0;
}
