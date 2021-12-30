/*************************************************************************
	> File Name: hello.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Mon Oct 18 12:06:14 2021
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int add(int, int);
int sub(int, int);
int mul(int, int);

int main(int argc, char *argv[]) {
	int a = 10, b = 5;
	printf("%d + %d = %d\n", a, b, add(a,b));
	printf("%d - %d = %d\n", a, b, sub(a,b));
	printf("%d * %d = %d\n", a, b, mul(a,b));
    return 0;
}
