/*************************************************************************
	> File Name: vector.h
	> Author: 我不是让神
	> Motto: Barefoot makes wheels
	> Created Time: Thu 24 Jun 2021 10:45:54 PM CST
 ************************************************************************/

#ifndef _VECTOR_H
#define _VECTOR_H
namespace rs {
template<typename T>
class vector {
public:
    int __size, __capacity;
    T *data;
};


}   // end of rs
#endif
