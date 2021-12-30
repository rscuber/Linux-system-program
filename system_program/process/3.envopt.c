/*************************************************************************
	> File Name: 3.envopt.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 05:08:56 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    //只是改了子进程的环境变量
    printf("path value = [%s]\n", getenv("PATH"));
    setenv("PATH", "hello", 1);
    printf("path value = [%s]\n", getenv("PATH"));

    /*
    extern char **environ;  //外部定义了environ
    for (int i = 0; environ[i]; i++) {
        printf("%s\n", environ[i]);
    }
    */
    return 0;
}
