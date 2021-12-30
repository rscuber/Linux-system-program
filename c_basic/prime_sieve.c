/*************************************************************************
	> File Name: prime_sieve.c
	> Author: rscuber
	> Mail: 1690661208@qq.com
	> Created Time: Thu 17 Dec 2020 09:45:56 AM CST
 ************************************************************************/

#include <stdio.h>
#define max_n 100 

int prime[max_n + 5];

void init() {
    for (int i = 2; i <= max_n; i++) {
        if (prime[i]) continue;
        prime[++prime[0]] = i;
        for (int j = i * i; j <= max_n; j += i) {
            prime[j] = 1;
        }
    }
    return;
}


int main() {
    init();
    for (int i = 1; i <= prime[0]; i++) {
        printf("%d\n", prime[i]);
    }
    return 0;
}
