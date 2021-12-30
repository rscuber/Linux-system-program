#!/usr/bin/env python
# coding=utf-8

# dic = {}
# dic = dict() 
# 键是唯一的
dic = {"name": "ycr", "age": 22, "class": 'A'}
print(dic)
print(len(dic))
print("str(dic): ", str(dic))
print(dic.keys())
print(dic.values())
for key, value in dic.items():
    print(key, value)

dic1 = {"like": "cube", "height": 182}
dic.update(dic1)
print("update dic: ", dic)

print("------------")
print(dic.get("name"))
print(dic.get("Name", "not found"))
dic["age"] = 23
print(dic["age"])
# del 会删除对应空间
del dic["class"]
print(dic)
dic.clear()
print(dic)
