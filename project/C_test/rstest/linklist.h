/*************************************************************************
	> File Name: linklist.h
	> Author: rscuber
	> Mail: 1690661208@qq.com
	> Created Time: Mon 14 Dec 2020 09:11:55 AM CST
 ************************************************************************/

#ifndef _LINKLIST_H
#define _LINKLIST_H

#define offset(T, name) (long long)(&(((T *)(0))->name))
#define Head(p, T, name) (T *)((char *)(p) - offset(T, name))

struct LinkNode {
    struct LinkNode *next;
};

#endif
