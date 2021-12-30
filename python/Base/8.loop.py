#!/usr/bin/env python
# coding=utf-8

sum1 = 0
i = 1
while i <= 100:
    sum1 += i
    i += 1
print("sum1 = ", sum1)

str = 'qwe'
for i in range(len(str)):
    print(str[i])

sum2 = 0
for i in range(1, 101):
    sum2 += i
print("sum2 = ", sum2)

# 嵌套循环
item = [[1, 3, 5], [11, 22, 33], [7, 8, 9]]
for i in item:
    for j in i:
        print(j)

