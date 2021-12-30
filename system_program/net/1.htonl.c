/*************************************************************************
	> File Name: 1.htonl.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Fri 16 Jul 2021 09:28:00 PM CST
 ************************************************************************/

#include <stdio.h>
#include <arpa/inet.h>

int main() {
    printf("INADDR_ANY: %#x\n", INADDR_ANY);
    printf("INET_ADDRSTRLEN = %d\n", INET_ADDRSTRLEN);
    int a = 0x12345678;
    char *p = (char *)(&a);
    printf("a = %#x\n", a);
    printf("addr: %p\t %#x\n", p, p[0]);
    printf("addr: %p\t %#x\n", p + 1, p[1]);
    printf("addr: %p\t %#x\n", p + 2, p[2]);
    printf("addr: %p\t %#x\n", p + 3, p[3]);
    int na = htonl(a);
    char *np = (char *)(&na);
    printf("na = %#x\n", na);
    printf("addr: %p\t %#x\n", np, np[0]);
    printf("addr: %p\t %#x\n", np + 1, np[1]);
    printf("addr: %p\t %#x\n", np + 2, np[2]);
    printf("addr: %p\t %#x\n", np + 3, np[3]);
    return 0;
}
