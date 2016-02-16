#!/bin/bash

function show_help { 
    echo "./doLimits.sh [-c to clean up]" 
}

cleanUp=0

while getopts "h?c" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    c)  cleanUp=1
        ;;
    esac
done

if [ $cleanUp -eq 0 ]; then
    ./buildInputs.sh
    ./buildDatacards.sh
    ./runLimits.sh
fi

if [ $cleanUp -eq 1 ]; then
    ./cleanUp.sh
fi
