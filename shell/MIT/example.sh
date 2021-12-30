#!/bin/bash

echo "Starting program at $(date)"  # $(cmd)
echo "Running program $0 with $# arguments with pid $$"
for file in "$@"; do
    grep foobar "$file" > /dev/null 2> /dev/null
    #if [[ "$?" -ne 0 ]]; then
    if [ $? ]; then
        echo "File $file not have any foobar, adding one"
        echo "# foobar" >> "$file"
    fi
done
