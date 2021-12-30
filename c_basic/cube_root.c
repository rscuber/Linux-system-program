/*************************************************************************
	> File Name: cube_root.c
	> Author: CodeCuber
	> Motto: Barefoot makes wheels
	> Created Time: 六  6/19 10:46:20 2021
 ************************************************************************/

#include <stdio.h>
#include <math.h>

double cubeRoot(double x) {
    return pow(x, 1.0 / 3);
}

int main() {
    double x; 
    while (~scanf("%lf", &x)) {
        printf("The cube root of %g is %g\n", x, cubeRoot(x));
    }
    return 0;
}
