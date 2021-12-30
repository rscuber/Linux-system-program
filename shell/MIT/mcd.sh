#!/bin/bash

function mcd() {
    mkdir -p "$1"
    cd "$1" || exit
}
# foobar
