#!/usr/bin/env python
# coding=utf-8

from datetime import datetime

mybirth = datetime(1999, 7, 19)

def MulPrintBirth(birth):
    print(birth.strftime("%Y-%m-%d"))
    print(birth.strftime("%Y-%B-%d"))
    print(birth.strftime("%Y-%b-%d"))
    print(birth.strftime("%x"))
    print(birth.strftime("%B-%d %Y"))
    print(birth.strftime("%B/%d/%Y"))
    print(birth.strftime("%B/%d/%Y"))
    print(birth.strftime("%m/%d/%Y"))
    return

MulPrintBirth(mybirth)
