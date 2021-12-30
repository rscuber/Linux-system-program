/*************************************************************************
	> File Name: 17.mmap.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 10:56:03 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main() {
    int fd = open("./test", O_RDWR);
    if (fd < 0) {
        perror("open file");
        exit(1);
    }

    /*
    int *p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
    ((int *)((char *)p + 1))[0] = 0x30313233;
    */

    char *p = mmap(NULL, 6, PROT_WRITE, MAP_SHARED, fd, 0);
    p[0] = 'A';
    p[1] = 'B';
    p[3] = 'C';
    munmap(p, 6);
    return 0;
}
