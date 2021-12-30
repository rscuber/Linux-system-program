#!/usr/bin/env python
# coding=utf-8

# 列表
list1 = ['red', 'green', 'yellow', 'blue', 'purple'];
print(list1[0])
print(list1[-1])
print(list1[1:-2])
print(list1)
list1.append('black')
del list1[0]
list1.remove('green');
list1.pop()
list1.pop(2)
print(list1)
print(len(list1))

a = [1, 2, 3]
b = [4, 5, 6]
print(a * 2)
a.extend(b)
print(a)

c = 1
if c in a:
    print("True")
else:
    print("False")

list2 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print(list2)
print(list2[0][1])
print(len(list2))
print(max(list2))
print(min(list2))

str1 = "abc"
list3 = list(str1)
print(list3)
str2 = str(list3)
print(str1)
print(str2)

# 排序
item = [3, 6, 1, 4, 5, 9, 0]
item.sort()
print(item)
item.sort(reverse = True)
print(item)
