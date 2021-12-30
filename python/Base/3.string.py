#!/usr/bin/env python
# coding=utf-8

str = "rang"
print(str[0])
print(str[-1])
print(str[:])
print(str[0:])
print(str[:3])
s = "hello"
print(str + s)
print(s * 2)
a = 'r'
if a in str:
    print("r is in str")
else:
    print("r is not in str")

print(str.capitalize())
print(str.center(10, 'x'))

str_utf8 = str.encode("UTF-8")
str_gbk = str.encode("GBK")
print("str_utf8 = ", str_utf8)
print("str_gbk = ", str_gbk)
print("str_utf8.decode('UTF-8', 'strict') = ", str_utf8.decode('UTF-8', 'strict'));
print("str_gbk.decode('gbk', 'strict') = ", str_gbk.decode('GBK', 'strict'))

s1 = "123aaa"
s2 = "123456"
print(str, ".isalnum() = ", str.isalnum())
print(str, ".isalnum() = ", s1.isalnum())
print(str, ".isalpha() = ", s1.isalpha())
print(s1, ".isalpha() = ", s2.isalpha())
print(str, ".isdigit() = ", str.isdigit())

