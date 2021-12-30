#!/usr/bin/env python
# coding=utf-8

# python注释
# 这是单行注释
"""
这是多行注释
"""

# 缩进
a = 1
b = 2
if a == b:
    print("true")
else:
    print("false")

# 多行语句
item_one = 1
item_two = 2
item_three = 3
total = item_one + \
        item_two + \
        item_three
print(total)

# python引号
word = 'word'
sentence = "this is a sentence"
paragraph = """
    this is a paragraph
"""

# 输入输出
# input返回值是string类型
#a = int(input())
#b = int(input())
#print(a + b)

# 多个变量同时赋值
a = b = c = 1
a, b, c = 1, 3.14, 'hello'

# 数据类型
"""
1.numbers(数字)
2.string(字符串)
3.list(列表)    a = [1, 2, 3]
4.tuple(元祖)   a = (1, 2, 3)
5.dict(字典)    a = {'ycr': 666}
"""

# 数字: 整型(int), 长整型(long), 浮点型(float), 复数(complex)
a = 1
b = 3.14

# 字符串
s = "yuanchengrang"
# 字符串长度
print(len(s))
# 截取字符串(左闭右开)
print(s[:4])    # 'yuan'
print(s[4:9])   # 'cheng'
print(s[:-1])   # 'yuanchengran'
print(s[::-1])  # 逆序
for i in s:
    print(i)

# 列表
a = []
a.append(1)
a.append(2)
a.remove(1)
print(a)

# 元祖(不可变)
a = ("ycr", 22, 1.23, 'A')
print(a[:3])

# 字典(键值对) 
a = {'aaa': 123, 'zzz': 789}
print(a.keys())
print(a.values())

# 算术运算符 
a = 5
b = 2
print(a + b)    # 7 
print(a - b)    # 3
print(a * b)    # 10
print(a / b)    # 2.5 (python3); python2版本答案是2
print(a % b)    # 1
print(a ** b)   # 25
print(a // b)   # 2

# 逻辑运算符: and, or, not

# 成员运算符: in, not in
x = 1
y = 6
item = [1, 2, 3]
if x in item:
    print("x is in item")
if y not in item:
    print("y is not in item")

# 条件语句
a = 5
if a > 10:
    print("a > 10")
elif a > 3:
    print("3 < a <= 10")
else:
    print("else ...")


