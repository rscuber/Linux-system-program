/*************************************************************************
	> File Name: test.h
	> Author: rscuber
	> Mail: 1690661208@qq.com
	> Created Time: Thu 10 Dec 2020 11:59:57 PM CST
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#include <rstest/linklist.h>

#define TEST(a, b)\
void a##_rs_##b();\
__attribute__((constructor))\
void add##_rs_##a##_rs_##b() {\
    add_function(a##_rs_##b, #a "_rs_" #b);\
}\
void a##_rs_##b()

#define COLOUR(a, b) "\033[" #b "m" a "\033[0m"
#define COLOUR_HL(a, b) "\033[1;" #b "m" a "\033[0m"

#define RED(a) COLOUR(a, 31)
#define GREEN(a) COLOUR(a, 32)
#define YELLOW(a) COLOUR(a, 33)
#define BLUE(a) COLOUR(a, 34) 

#define RED_HL(a) COLOUR_HL(a, 31) 
#define GREEN_HL(a) COLOUR_HL(a, 32)
#define YELLOW_HL(a) COLOUR_HL(a, 33)
#define BLUE_HL(a) COLOUR_HL(a, 34)


#define TYPE(a) _Generic((a),\
    int : "%d",\
    float : "%f",\
    double : "%lf",\
    long long : "%lld",\
    const char * : "%s",\
    char * : "%s"\
    )

#define P(a, colour) {\
    char frm[1000];\
    sprintf(frm, colour("%s"), TYPE(a));\
    printf(frm, a);\
}

#define EXPECT(a, b, comp) {\
    rstest_info.total += 1;\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    if (a comp b) rstest_info.success += 1;\
    else {\
        printf("\n");\
        printf(YELLOW_HL("\t%s:%d Failure\n"), __FILE__, __LINE__);\
        printf(YELLOW_HL("\t\texpect : %s\n\t\tactual : "), #a " " #comp " " #b);\
        P(_a, YELLOW_HL);\
        P(" vs ", YELLOW_HL);\
        P(_b, YELLOW_HL);\
        printf("\n\n");\
    }\
    printf(GREEN("[-----------] ") #a " " #comp " " #b);\
    printf(" %s\n", _a comp _b ? GREEN_HL("True") : RED_HL("False"));\
}

#define EXPECT_EQ(a, b) EXPECT(a, b, ==) 
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)


typedef void (*Testfunc)();

int RUN_ALL_TESTS();

void add_function(Testfunc, const char *);

typedef struct Function {
    Testfunc func;
    const char *str;
    struct LinkNode p;
} Function;

typedef struct FunctionInfo {
    int total, success;
} FunctionInfo;

extern Function func_head, *fun_tail;
extern FunctionInfo rstest_info;

#endif
