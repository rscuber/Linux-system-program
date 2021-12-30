/*************************************************************************
	> File Name: test.c
	> Author: rscuber
	> Mail: 1690661208@qq.com
	> Created Time: Fri 11 Dec 2020 12:14:40 AM CST
 ************************************************************************/
#include <stdio.h>
#include <rstest/test.h>
#include <rstest/linklist.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Function func_head, *func_tail = &func_head;
FunctionInfo rstest_info;

int RUN_ALL_TESTS() {
    for (struct LinkNode *p = func_head.p.next; p; p = p->next) {
        Function *func = Head(p, Function, p);
        printf(GREEN("[====RUN====]") RED_HL(" %s\n"), func->str);
        rstest_info.total = 0, rstest_info.success = 0;
        func->func();
        double rate = 100.0 * rstest_info.success / rstest_info.total;
        printf(GREEN("[  "));
        if (fabs(rate - 100.0) < 1e-6) {
            printf(BLUE_HL("%6.2lf%%"), rate);
        } else {
            printf(RED_HL("%6.2lf%%"), rate);
        }
        printf(GREEN("  ]") " total : %d    success : %d\n", 
            rstest_info.total,
            rstest_info.success
        );
        printf("\n");
    }
}

void add_function(Testfunc func, const char *str) {
    Function *temp = (Function *)calloc(1, sizeof(Function));
    temp->func = func;
    temp->str = strdup(str);
    func_tail->p.next = &(temp->p);
    func_tail = temp;
    return;
}
