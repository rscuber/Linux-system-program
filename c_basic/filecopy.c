/*************************************************************************
	> File Name: filecopy.c
	> Author: CodeCuber
	> Mail: 1690661208@qq.com
	> Created Time: 六  6/12 08:57:54 2021
 ************************************************************************/

#include <stdio.h>

void filecopy(FILE *in_fp, FILE *out_fp) {
    char ch;
    while ((ch = fgetc(in_fp)) != EOF) {
        fputc(ch, out_fp);
    }
    return ;
}

int main(int argc, char **argv) {
    FILE *fp1 = fopen("./argv1", "r");
    FILE *fp2 = fopen("./argv2", "w");
    filecopy(fp1, fp2);
    return 0;
}
