/*************************************************************************
	> File Name: getopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 12 Sep 2021 11:22:58 AM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "xy:z::")) != -1) {
        switch (opt) {
            case 'x': {
                printf("opt x found, optind = %d\n", optind);
                printf("optarg for x is %s\n", optarg);
                printf("argv[%d] = %s\n\n", optind, argv[optind]);
            } break;
            case 'y': {
                printf("opt y found, optind = %d\n", optind);
                printf("optarg for y is %s\n", optarg);
                printf("argv[%d] = %s\n\n", optind, argv[optind]);
            } break;
            case 'z': {
                printf("opt z found, optind = %d\n", optind);
                printf("optarg for z is %s\n", optarg);
                printf("argv[%d] = %s\n\n", optind, argv[optind]);
            } break;
            default: {
                fprintf(stderr, "Usage: %s -x -y yarg -z[zarg]\n", argv[0]);
                exit(1);
            }
        }
    } 
    if (opt == -1) perror("getopt");
    return 0;
}
