#!/usr/bin/env python
# coding=utf-8

class Vector:
    x = 0
    y = 0
    def __init__(self, x, y):
        self.x = x
        self.y = y
        return 
    def __str__(self):
        return "Vector(%d, %d)" % (self.x, self.y)
    def __add__(self, obj):
        return Vector(self.x + obj.x, self.y + obj.y)
    def __del__(self):
        del self.x
        del self.y
        return 

v1 = Vector(2, 3)
v2 = Vector(5, 6)
print("v1 + v2 = ", v1 + v2)


