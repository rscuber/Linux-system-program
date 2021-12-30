#!/usr/bin/env python
# coding=utf-8

# 创建空集合
set1 = set()

# 添加
set1.add('hello')
set1.add('world')
set1.add('aaa')
set1.add('qwe')

# 删除
set1.remove('qwe')
set1.discard('qwe')
a = set1.pop()
print("a = ", a)
print(set1)
if 'aaa' in set1:
    print("aaa is in set1")
else:
    print("not in")
