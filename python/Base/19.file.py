#!/usr/bin/env python
# coding=utf-8


# f = open("test.txt", "w", encoding = 'utf-8')
f = open("test.txt", "w")
num = f.write("hello world\nwelcome rs\nyuan cheng rang\n")
print("num = ", num)
print("type(num): ", type(num))
f.close()

f = open("test.txt", "r")
s1 = f.read()
print(s1, end = '')
f.close()

print("--------")

f = open("test.txt", "r")
s2 = f.readline()
print(s2, end = '')
f.close()
print("--------")

f = open("test.txt", "r")
data = f.readlines()
for sdata in data:
    print(sdata)
f.close()

f = open("site.txt", "w")
value = ("baidu.com", 666)
s = str(value)
f.write(s)
f.close()
