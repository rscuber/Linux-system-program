#!/usr/bin/env python
# coding=utf-8

class People:
    # 定义公有属性
    name = ''
    age = 0
    # 定义私有属性
    __weight = 0
    def __init__(self, name, age, weight):
        self.name = name
        self.age = age
        self.weight = weight
        return 
    def getWeight(self): 
        return self.weight
    def introduce(self):
        print("name = ", self.name, "age = ", self.age)
        return 
    def myMethod(self):
        print("this is parent")
        return 

class Student(People):
    grade = 0
    def __init__(self, name, age, weight, grade):
        People.__init__(self, name, age, weight)
        self.grade = grade
        return 
    def __printObj(self):
        print("self = ", self)
        print('self.__class__  = ', self.__class__)
    def introduce(self):
        self.__printObj()
        print("name = ", self.name, ", grade = ", self.grade)
        return 
    def myMethod(self):
        print("this is child")
        return 

a = Student("aaa", 20, 150, 3)
a.introduce()
a.myMethod()
super(Student, a).myMethod()

