/*************************************************************************
	> File Name: 3.raise.c
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed 07 Jul 2021 05:03:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    sleep(1);
    //raise(SIGSEGV);
    abort();
    return 0;
}
