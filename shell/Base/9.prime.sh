#!/bin/bash
function Usage() {
    echo "Usage : bash $0 Start_num End_num"
    exit
}
function is_prime() {
    num=$1
    local i
    for ((i=2; i<${num}; i++));do
        if [[ $[ ${num} % ${i} ] -eq 0 ]];then
            return 1
        fi
    done
    return 0
}
if [[ $# -ne 2 ]];then
    Usage
fi

Start=$1
End=$2
if [[ ${Start} -lt 2 ]];then
    Start=2
fi
for ((i=${Start}; i<=${End}; i++));do
    is_prime $i
    if [[ $? -eq 0 ]];then
        sum=$[ ${sum} + ${i} ]
    fi
done

echo ${sum}
