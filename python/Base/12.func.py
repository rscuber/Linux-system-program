#!/usr/bin/env python
# coding=utf-8

def max(a, b):
    if (a >= b):
        return a
    else:
        return b

def area(width, high):
    return width * high / 2

print("max(1, -1) = ", max(1, -1))
print("tirangle area(3, 4) = ", area(3, 4))

def change(a):
    print('after called, before assign: ', id(a))
    a = 10
    print('after assign: ', id(a))

a = 1
print('before called: ', id(a))
change(a)

def changeme(mylist):
    mylist.append('a')
    print('after called: ', mylist)

mylist = [1, 2, 3]
print('before called: ', mylist)
changeme( mylist)

def output(str1, str2 = 'hello'):
    print('str1 = ', str1)
    print('str2 = ', str2)
    return 

output('hello', 'world')
output('ycr')

def printInfo(name, age):
    print('name: ', name)
    print('age: ', age)
    return 

printInfo('ycr', 22)
printInfo(age = 22, name = 'ycr')

def printVar(arg1, *vartuple):
    print('all args: ', arg1, vartuple)
    return 

printVar('A', 123, 'hello', 3.14)

def printVar2(arg1, **vardic):
    print('all args: ', arg1, vardic)
    return 

printVar2(1, a = 123, b = 789)

def sum1(a, b):
    return a + b
sum2 = lambda arg1, arg2: arg1 + arg2
print('sum1(123, 5) = ', sum1(123, 5))
print('sum2(123, 5) = ', sum2(123, 5))
