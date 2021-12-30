/*************************************************************************
	> File Name: myls.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 11 Sep 2021 12:01:32 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <color.h>

void absolute_path(char *ab_path, char *path, char *filename) {
    strcpy(ab_path, path);
    strcat(ab_path, "/");
    strcat(ab_path, filename);
    return ;
}

void mode2str(mode_t smode, char *mode, char *color) {
    int i = 0;
    //rwx数组分别对应着000、001、...、110、111
    char *rwx[] = {
        "---", "--x", "-w-",
        "-wx", "r--", "r-x",
        "rw-", "rwx"
    };
    switch (smode & S_IFMT) {
        case S_IFREG:  mode[0] = '-';                           break;
        case S_IFDIR:  mode[0] = 'd'; strcpy(color, "BLUE_HL"); break;
        case S_IFCHR:  mode[0] = 'c';                           break;
        case S_IFIFO:  mode[0] = 'p';                           break;
        case S_IFLNK:  mode[0] = 'l'; strcpy(color, "CYAN_HL"); break;
        case S_IFBLK:  mode[0] = 'b';                           break;
        case S_IFSOCK: mode[0] = 's';                           break;
        default: mode[i++] = '?';
    }
    //获取文件权限
    strcpy(&mode[1], rwx[(smode >> 6) & 7]); 
    strcpy(&mode[4], rwx[(smode >> 3) & 7]);
    strcpy(&mode[7], rwx[smode & 7]);
    //获取文件特殊权限
    if (smode & S_ISUID) mode[3] = (smode & S_IXUSR) ? 's' : 'S';
    if (smode & S_ISGID) mode[6] = (smode & S_IXGRP) ? 's' : 'S';
    if (smode & S_ISVTX) mode[0] = (smode & S_IXOTH) ? 't' : 'T';
    if (mode[0] == '-') {
        if (strstr(mode, "x")) strcpy(color, "GREEN_HL");
        if (strstr(mode, "s") || strstr(mode, "S")) strcpy(color, "YELLOW_HB");
    }
    if (mode[0] == 't') strcpy(color, "GREEN_BG");
    return ;
}

void mtim2str(struct timespec *mtim, char *str, size_t max) {
    struct tm *tmp_time = localtime(&mtim->tv_sec); // 转换为当地日历时间
    strftime(str, max, "%b %e %H:%M", tmp_time); // 转换为指定格式
    return ;
}

void myls(char *path, int a_flag) {
    // 0. 按 [字典序] 读取出目录的文件列表
    struct dirent **namelist;
    int i = -1;
    int n = scandir(path, &namelist, NULL, alphasort); // 按字典序读
    if (n == -1) {
        perror("scandir");
        exit(1);
    }
    //正序遍历文件列表
    while (i < n - 1) {
        i++;
        DIR *dirp;
        struct dirent *dent = namelist[i];
        if (dent->d_name[0] == '.' && !a_flag) continue; //是否显示隐藏文件
        struct stat st;                                  //需要为该结构体开辟内存
        char ab_path[128];                               //记录绝对路径
        absolute_path(ab_path, path, dent->d_name);      //+. 路径拼接
        // 1. 读取文件信息
        if (!lstat(ab_path, &st)) {
            char mode[16], mtime[32], uname[16];
            char gname[16], filename[512], color[16] = {0};
            mode2str(st.st_mode, mode, color);      //2.处理文件信息 [并设置颜色]
            mtim2str(&st.st_mtim, mtime, sizeof(mtime));  //3. 处理修改时间
            strcpy(uname, getpwuid(st.st_uid)->pw_name);  //4. 获取文件所属者名称
            strcpy(gname, getgrgid(st.st_gid)->gr_name);  //5. 获取文件所属组名称
            //打印除文件名外的基本信息
            printf("%s %*lu %s %s %*lu %s ",
                mode, 3, st.st_nlink, uname, gname, 5, st.st_size, mtime
            );
            //6. 根据颜色包装文件名
            if (!strcmp(color, "BLUE")) {
                sprintf(filename, BLUE("%s"), dent->d_name);
            } else if (!strcmp(color, "BLUE_HL")) {
                sprintf(filename, BLUE_HL("%s"), dent->d_name);
            } else if (!strcmp(color, "GREEN_HL")) {
                sprintf(filename, GREEN_HL("%s"), dent->d_name);
            } else if (!strcmp(color, "YELLOW_HB")) {
                sprintf(filename, YELLOW_BG("%s"), dent->d_name);
            } else if (!strcmp(color, "GREEN_BG")) {
                sprintf(filename, GREEN_BG("%s"), dent->d_name);
            } else {
                strcpy(filename, dent->d_name);
            }
            //7.对软连接特殊处理
            if (mode[0] == 'l') {
                char linkfile[32];
                readlink(ab_path, linkfile, 32);
                strcat(filename, "->");
                strcat(filename, linkfile);
            }
            //单独打印文件名称[含颜色]
            printf("%s\n", filename);
        } else {
            perror("lstat");
            exit(1);
        }
        free(namelist[i]);
    }
    free(namelist);
    return ;
}

void show_tips(char **argv) {
    fprintf(stderr, "Usage: %s -[a]l [path]\n", argv[0]);
    return ;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        show_tips(argv);
        exit(1);
    }
    //不带路径参数 [默认为当前目录]
    if (argc == 2) {
        if (!strcmp(argv[1], "-al")) myls(".", 1);
        else if (!strcmp(argv[1], "-l")) myls(".", 0);
        else show_tips(argv), exit(1);
        return 0;
    }
    int opt;
    int a_flag = 0; //判断-a选项
    //带路径参数
    while ((opt = getopt(argc, argv, "al:")) != -1) {
        switch (opt) {
            case 'a': a_flag = 1; break;
            case 'l': myls(optarg, a_flag); break;
            default: {
                show_tips(argv);
                exit(1);
            }
        } 
    }
    return 0;
}
