#!/bin/bash
sum=0
for ((i=1; i<=100; i++));do
    if [[ $[ ${i} % 2 ] -eq 0 ]];then
        sum=$[ ${i} + ${sum} ]
    fi
done

echo "sum = ${sum}"
