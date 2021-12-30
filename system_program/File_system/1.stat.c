/*************************************************************************
	> File Name: 1.stat.c
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Fri 18 Jun 2021 11:39:05 AM CST
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat st;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int n = lstat(argv[1], &st);
    if (n == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    /*
    if (S_ISREG(st.st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(st.st_mode)){
        printf("directory\n");
    } else {
        printf("other file type\n");
    }
    */
    printf("ID of containing device:  [%lx,%lx]\n", 
        (long)major(st.st_dev), (long)minor(st.st_dev)
    ); 
    printf("File type:                ");
    switch (st.st_mode & S_IFMT) {
        case S_IFREG:  printf("regular file\n");      break;
        case S_IFDIR:  printf("directory\n");         break;
        case S_IFCHR:  printf("character device\n");  break;
        case S_IFIFO:  printf("FIFO/pipe\n");         break;
        case S_IFLNK:  printf("symlink\n");           break;
        case S_IFBLK:  printf("block device\n");      break;
        case S_IFSOCK: printf("socket\n");           break;
        default:       printf("unknown\n");           break;
    }
    printf("I-node number:            %ld\n", (long)st.st_ino);
    printf("Mode:                     %lo(ocatl)\n", (unsigned long)st.st_mode);
    printf("Link count:               %ld\n", (long)st.st_nlink);
    printf("Ownership:                Uid=%ld     Gid=%ld\n", 
        (long)st.st_uid, (long)st.st_gid
    );
    printf("Preferred I/O block size: %ld bytes\n", (long)st.st_blksize);
    printf("File size:                %lld\n", (long long)st.st_size);
    printf("Blocks allocated:         %lld\n", (long long)st.st_blocks);
    printf("Last status change:       %s", ctime(&st.st_ctime));
    printf("Last file access:         %s", ctime(&st.st_atime));
    printf("Last file modification:   %s", ctime(&st.st_mtime));
    exit(EXIT_SUCCESS);
    return 0;
}
