#!/usr/bin/env python
# coding=utf-8

# 元祖的元素不能修改
# tup1 = ()
tup1 = (1, 2, 3)
tup2 = (4, 5, 6)
tup3 = tup1 + tup2
print(tup3[1:-1])
print(len(tup2))
# 删除tup3空间
del tup3

if 1 in tup1:
    print(min(tup1))
else:
    print(max(tup1))
