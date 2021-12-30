#!/usr/bin/env python
# coding=utf-8

import random
target = random.randint(0, 10)
cnt = 1
while True:
    try:
        x = eval(input("请输入一个数:"))
        if x < target:
            print("遗憾，太大了")
        elif x > target:
            print("遗憾，太小了")
        else:
            print("预测%d次, 你猜中了" % cnt)
            break
    except NameError:
        print("请输入一个整数")
    except:
        print("其他错误")
    finally:
        print("程序执行完毕，没有异常")


