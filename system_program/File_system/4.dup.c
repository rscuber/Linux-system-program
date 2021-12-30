/*************************************************************************
	> File Name: 4.dup.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Thu 01 Jul 2021 07:04:09 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fd, save_fd;
    fd = open("test.txt", O_RDWR);    // fd = 3
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("fd = %d\n", fd);
    save_fd = dup(1);                 //save_fd = 4
    printf("save_fd = %d\n", save_fd);
    dup2(fd, 1);
    close(fd);
    write(1, "1234567890\n", 11);       //往test.txt上写
    dup2(save_fd, 1);                 //1重新指回stdout, 此时系统close test.txt
    write(1, "1234567890\n", 11);       //往test.txt上写
    close(save_fd);                //save_fd消失,指向stdout的指针-1,但stdout并没关闭
    return 0;
}
