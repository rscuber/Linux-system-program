/*************************************************************************
	> File Name: 6.callback.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 11:12:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc - 3) {
        fprintf(stdout, "Usage: %s <inputfile> <outputfile>\n", argv[0]);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open read");
        exit(EXIT_FAILURE);
    }
    dup2(fd, 0);
    close(fd);
    fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open write");
        exit(EXIT_FAILURE);
    }
    dup2(fd, 1);
    close(fd);
    execl("./upper", "./upper", NULL);
    perror("exec");
    exit(1);
    return 0;
}
