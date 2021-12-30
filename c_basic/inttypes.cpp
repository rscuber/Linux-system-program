/*************************************************************************
	> File Name: inttypes.cpp
	> Author: 我不是让神
	> Mail: 1690661208@qq.com
	> Created Time: 日  1/ 3 11:31:29 2021
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>

int main() {
    int32_t a = 70000;
    printf("short short: %%%s\n", PRId8);
    printf("short: %%%s\n", PRId16);
    printf("int: %%%s\n", PRId32);
    printf("long long: %%%s\n", PRId64);
    printf("a = %" PRId32 "\n", a);
    //强转成char可以消除警告
    printf("INT8_MIN = %" PRId8 " \t INT8_MAX = %" PRId8 "\n", INT8_MIN, INT8_MAX);
    printf("INT16_MIN = %" PRId16 " \t INT16_MAX = %" PRId16 "\n", INT16_MIN, INT16_MAX);
    printf("INT32_MIN = %" PRId32 " \t INT32_MAX = %" PRId32 "\n", INT32_MIN, INT32_MAX);
    printf("INT64_MIN = %" PRId64 " \t INT64_MAX = %" PRId64 "\n", INT64_MIN, INT64_MAX);
    return 0;
}
