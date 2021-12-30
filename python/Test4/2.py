#!/usr/bin/env python
# coding=utf-8

def multi(*vartuple):
    sum, mul = 0, 1
    for i in vartuple:
        sum += i
        mul *= i
    return [sum, mul]

print(multi(1, 2, 3, 4, 5))
