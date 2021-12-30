#!/usr/bin/env python
# coding=utf-8

class Heap:
    def __init__(self):
        self.data = [0]
    def pushList(self, nums):
        for i in nums:
            self.push(i)
        return 
    def top(self):
        return self.data[1]
    def size(self):
        return len(self.data) - 1
    def isEmpty(self):
        return len(self.data) == 1
    def upMaintain(self, idx):
        while idx >> 1 and self.data[idx] > self.data[idx >> 1]:
            self.data[idx], self.data[idx >> 1] = self.data[idx >> 1], self.data[idx]
            idx >>= 1
        return 
    def downMaintain(self, idx):
        while (idx << 1) <= self.size():
            l, r, temp = idx << 1, idx << 1 | 1, idx
            if self.data[l] > self.data[temp]: temp = idx
            if r <= self.size() and self.data[r] > self.data[temp]: temp = r
            if idx == temp: break
            self.data[idx], self.data[temp] = self.data[temp], self.data[idx]
            idx = temp
        return 
    def push(self, val):
        self.data.append(val)
        self.upMaintain(self.size())
        return True
    def pop(self):
        if self.size() <= 0: return False
        self.data[1] = self.data[-1]
        self.data.pop()
        self.downMaintain(1)
        return True

if __name__ == '__main__':
    h = Heap()
    arr = [1, 2, 3, 4, 5]
    h.pushList(arr)
    while not h.isEmpty():
        print(h.top(), end = ' ')
        h.pop()
    print()
