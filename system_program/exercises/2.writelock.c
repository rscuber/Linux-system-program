/*************************************************************************
	> File Name: 2.writelock.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sun 11 Jul 2021 10:08:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("./1.test", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    struct stat sta;
    fstat(fd, &sta);
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_pid = getpid();
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sta.st_size;
    printf("pid: %d\t", lock.l_pid);
    while (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("error");
        struct flock lock_1 = lock;
        lock_1.l_type = F_WRLCK;
        fcntl(fd, F_GETLK, &lock_1);
        switch (lock_1.l_type) {
            case F_UNLCK: {
                printf("get no lock\n"); 
            } break;
            case F_RDLCK: {
                printf("get read lock of pid: %d\n", lock_1.l_pid);
            } break;
            case F_WRLCK: {
                printf("get write lock of pid: %d\n", lock_1.l_pid);
            } break;
        }
        sleep(1);
    }
    printf("set write lock successfully\n");
    getchar(); // 用于防止程序结束
    close(fd);
    return 0;
}
