/*************************************************************************
	> File Name: test.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Sat 10 Jul 2021 10:31:15 PM CST
 ************************************************************************/

#include <stdio.h>

int main() {
    FILE *fp = fopen("dict.dic", "r");
    char s[40];
    while (fgets(s, 33, fp)) {
        printf("%s", s);
    }
    return 0;
}
