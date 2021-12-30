#!/bin/bash
if [[ $# -ne 2 ]];then
    echo "Usage : bash $0 Start_num End_num"
    exit
fi
Start=$1
End=$2

declare -a Prime
sum=0

for (( i=2; i<=${End}; i++ ));do
    if [[ ${Prime[$i]}x == x ]];then
        Prime[0]=$[ ${Prime[0]} + 1 ]
        Prime[ ${Prime[0]} ]=$i
        sum=$[ ${sum} + ${i} ]
    fi
    for (( j=1; j<=${Prime[0]}; j++ ));do 
        if [[ $[ ${i} * ${Prime[$j]} ] -gt ${End} ]];then
            break
        fi
        Prime[ $[ ${i} * ${Prime[$j]} ]]=1
        if [[ $[ ${i} % ${Prime[$j]} ] -eq 0 ]];then
            break
        fi
    done
done

echo $sum
