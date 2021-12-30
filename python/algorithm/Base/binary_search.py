#!/usr/bin/env python
# coding=utf-8

def binary_search(arr, head, tail, target):
    while head <= tail:
        mid = (head + tail) >> 1
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            head = mid + 1
        else:
            tail = mid - 1
    return -1

def binary_search_v2(arr, head, tail, target):
    if head > tail: return 
    mid = (head + tail) >> 1
    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search_v2(arr, mid + 1, tail, target)
    else:
        return binary_search_v2(arr, head, mid - 1, target)
    return -1

def Test(bsfunc, arr, x):
    idx = bsfunc(arr, 0, len(arr), x)
    if idx != -1:
        print('find {} at {}'.format(x, idx))
    else:
        print('Not found!')
    return 

arr = [1, 3, 5, 7, 9]
Test(binary_search, arr, 5)
Test(binary_search_v2, arr, 5)
