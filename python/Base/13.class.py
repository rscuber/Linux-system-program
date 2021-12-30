#!/usr/bin/env python
# coding=utf-8

class Complex:
    # 定义基本属性
    real = 0
    imag = 0

    # 定义构造函数
    def __init__(self, real, imag):
        self.real = real
        self.imag = imag

    def output(self):
        print("self = ", self)
        print("self.__class__ = ", self.__class__)
        print("c = (", c.real, ", ", c.imag, ")")
        return 

c = Complex(2, 3)
c.output()
