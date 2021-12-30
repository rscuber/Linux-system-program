#!/bin/bash
path="../ls"
gcc myls.c -o myls

function test_myls() {
    echo -e "./myls $1 $2" | lolcat
    ./myls $1 $2
    echo ""
}

test_myls -al
test_myls -l
test_myls -a
test_myls -al $path
test_myls -l $path
test_myls -b $path
