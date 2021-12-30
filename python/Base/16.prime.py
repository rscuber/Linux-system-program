#!/usr/bin/env python
# coding=utf-8

n = int(input())
def is_prime(n):
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True

def output_prime(n):
    for i in range(2, n + 1):
        if is_prime(i):
            print(i)
    return 

output_prime(n)
