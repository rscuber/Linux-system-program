/*************************************************************************
	> File Name: filelock.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 11 Jul 2021 07:45:05 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("./1.test", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    struct stat sta;
    fstat(fd, &sta);
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sta.st_size;
    printf("pid: %d\t", lock.l_pid);
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    } else {
        printf("add read lock successfully\n");
    }
    sleep(10);
    close(fd);
    return 0;
}
