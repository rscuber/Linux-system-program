#!/bin/bash

# test 和 '[]' 都是shell内置命令, '[[  ]]'是关键字
test -f example.sh && echo "file exists" || echo "file not exists"
test ! -d /etc && echo "is not a directory" || echo "is a directory"

# 这里被解释为重定向
# [ 1 < 2 ] && echo "True" || echo "False" 

# = < > 是字符串比较
# [[ 1 < 2 ]] && echo "True" || echo "False"

#read str
str="hello world"
if [[ -n $str ]]; then
    echo "str is not null"
fi

if [[ $str = "hello world" ]]; then
    echo "str is hello world"
fi
