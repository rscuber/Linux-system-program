/*************************************************************************
	> File Name: test.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Mon Oct 25 14:46:37 2021
 ************************************************************************/

#include <stdio.h>

int sum(int);

int main() {
    int sum1;
    sum(50);
    for (int i = 1; i <= 50; i++) {
        sum1 += i;
    }
    printf("sum1 = %d\n", sum1);
    return 0;
}

int sum(int n) {
    int sum;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("sum = %d\n", sum);
    return 0;
}
