#!/usr/bin/env python
# coding=utf-8

class Node:
    def __init__(self):
        self.falg = False
        self.next = [None] * 26


class Trie:
    def __init__(self):
        self.root = Node()
    def insert(self, word):
        p = self.root
        for i in word:
            idx = ord(i) - ord('a')
            if p.next[idx] is None:
                p.next[idx] = Node()
            p = p.next[idx]
        p.flag = True
        return True
    def search(self, word):
        p = self.root
        for i in word:
            idx = ord(i) - ord('a')
            p = p.next[idx]
            if p is None:
                return False
        return p.flag

if __name__ == '__main__':
    tree = Trie()
    while True:
        op, word = input().split()
        if op == '0':
            print('{} insert {}'.format(word, 'successfully' if tree.insert(word) else 'failed' ))
        else:
            print('search {} {}'.format(word, 'successfully' if tree.search(word) else 'failed'))


