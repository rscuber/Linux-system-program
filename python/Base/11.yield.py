#!/usr/bin/env python
# coding=utf-8

import sys

def fibonacci(n):
    a, b = 0, 1
    counter = 0
    while True:
        if counter >= n:
            return 
        yield a
        a, b = b, a + b
        counter += 1

f = fibonacci(10)

while True:
    try:
        print(next(f))
    except StopIteration:
            sys.exit()
