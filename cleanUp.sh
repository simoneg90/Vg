#!/bin/bash 

postfix=(
    `cat inputs_to_process.txt`
)

mass=$1

for name in ${postfix[@]}
do
    echo removing ${mass}_${name}
    rm -rf info_${mass}_${name}
done
