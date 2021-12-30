/*************************************************************************
	> File Name: hello.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 02 Jul 2021 12:19:33 PM CST
 ************************************************************************/

#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    printf("hello %d\n", add(2, 3));
    char arr[10] = {"hello"};
    //const char *p = arr <==> char const *p = arr;
    const char *p = arr; // p所指向的内容是read-only
    //p[1] = 'A';   会报错
    char * const p1 = arr;//p1 is a read-only variable 
    //p1 = NULL; 会报错
    return 0;
}
