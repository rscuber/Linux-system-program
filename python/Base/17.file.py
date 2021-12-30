#!/usr/bin/env python
# coding=utf-8

try:
    f = open("./test", "r")
    print(f.read())
finally:
    if f:
        f.close()
        print("file is closed")

