#!/bin/bash
function Usage() {
    echo "bash $0 Start_num End_num"
    exit
}

if [[ $# -ne 2 ]];then
    Usage
fi

Start=$1
End=$2
declare -a Prime

function init() {
    local end=$1
    local i
    Prime[1]=1
    for ((i=2; i<=${end}; i++));do
        for ((j=${i} * ${i}; j<=${end}; j+=i));do
            Prime[j]=1
        done
    done
}

if [[ ${Start} -lt 2 ]];then
    Start=2
fi

init ${End}

for ((i=${Start}; i<=${End}; i++));do
    if [[ ${Prime[i]}x == x ]];then
        sum=$[ ${sum} + ${i} ]
    fi
done

echo ${sum}
