#!/usr/bin/env python
# coding=utf-8

s = 'hello'
print("str(s) = ", str(s))
print("repr(s) = ", repr(s))

x = 2 * 3.14
y = 123 + 5
s = 'x = ' + repr(x) + ', y = ' + repr(y)
print("s: ", s)

print('{}_address: "{}"'.format('baidu', 'www.baidu.com'))

# 根据索引进行格式化字符
print('{0}_address: "{1}"'.format('baidu', 'www.baidu.com'))
print('{1}_address: "{0}"'.format('baidu', 'www.baidu.com'))

# 根据关键字进行格式化字符
print('{name}_address: "{site}"'.format(name = 'baidu', site = 'www.baidu.com'))

# 根据索引和关键字结合进行格式化字符
print('a1: {0}, a2: {other}, a3: {1}'.format( 'dog', 'cat', other = 'tiger'))

import math
print("PI approximately equal to {0:.3f}".format(math.pi))

table = {'Google': 1, 'Baidu': 2, 'Bing': 3}
for name, number in table.items():
    print('{0:10} ==> {1:10d}'.format(name, number))

print('table[Bing] = ', table['Bing'])

print('Baidu: {0[Baidu]: d}, Google: {0[Google]: d}, Bing: {0[Bing]: d}'.format(table))

# 古老的语法, 不推荐
print("%d-%d" % ( 1, 2))
str = input("please input name:")
print('welcome {}'.format(str))
