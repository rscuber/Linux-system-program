/*************************************************************************
	> File Name: 12.lseek.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 17 Jun 2021 10:22:35 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd = open("./12.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    char c;
    read(fd, &c, 1);
    int pos1 = lseek(fd, 0, SEEK_CUR);
    printf("pos1 = %d\n", pos1);
    write(STDOUT_FILENO, &c, 1);
    write(STDOUT_FILENO, "\n", 1);
    int pos2 = lseek(fd, 3, SEEK_SET);
    printf("pos2 = %d\n", pos2);
    read(fd, &c, 1);
    write(STDOUT_FILENO, &c, 1);
    write(STDOUT_FILENO, "\n", 1);
    int pos3 = lseek(fd, 3, SEEK_CUR);
    printf("pos3 = %d\n", pos3);
    read(fd, &c, 1);
    write(STDOUT_FILENO, &c, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
}
