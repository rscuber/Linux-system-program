#!/usr/bin/env python
# coding=utf-8

str = input("请输入一个字符串:")
print("str = ",str)
a, b, c, = 0
for i in str:
    if i.isalpha(): 
        a += 1
    if i.isdigit():
        b += 1
    if i.isspace():
        c += 1
print("英文字符个数:", a)
print("数字字符个数:", b)
print("空格字符个数:", c)
