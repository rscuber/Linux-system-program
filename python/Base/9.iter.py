#!/usr/bin/env python
# coding=utf-8

import sys

list = [1, 2, 3, 4]
it = iter(list)
print(type(it))
print(it)
for i in range(len(list)):
    print(next(it))

list1 = [5, 6, 7, 8]
it = iter(list1)
for data in it:
    print(data)

list2 = ['a', 'b', 'c', 'd']
it = iter(list2)
while True:
    try:
        print(next(it))
    except StopIteration:
        sys.exit()
