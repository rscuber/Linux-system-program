#!/bin/bash
echo "Hello World!"
WorkDir=`pwd`
echo -e "In \033[31;32m ${WorkDir} \033[0m"
echo "Program Name : $0"
echo "Arg1 : $1"
echo "Arg2 : $2"
echo "Arg3 : $3"
echo "Arg4 : $4"
echo "Aeg5 : $5"
echo "\$@ : $@"
echo "\$* : $*"
echo "\$# : $#"
Name={rscuber}
last | grep "${Name}" 1>/dev/null 2>/dev/null 
if [[ $? -eq 0 ]];then
    echo -e "$Name logged in!\n"
fi
