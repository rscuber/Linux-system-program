/*************************************************************************
	> File Name: main.c
	> Author: rscuber
	> Mail: 1690661208@qq.com
	> Created Time: Thu 10 Dec 2020 11:55:11 PM CST
 ************************************************************************/

#include <stdio.h>
#include <rstest/test.h>

int add(int a, int b) {
    return a + b;
}

TEST(testfunc, add) {
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_GE(add(3, 5), 7);
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_GT(add(2, 3), 6)
}

TEST(testfunc, add2) {
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_LT(add(1, 3), 8);
}

TEST(test, funcadd2) {
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_NE(add(1, 3), 3);
    EXPECT_EQ(add(2, 3), 6);
}

int main(int argc, char *argv[]) {
    return RUN_ALL_TESTS();
}
