#!/bin/bash 

postfix=(
    `cat inputs_to_process.txt`
)

for name in ${postfix[@]}
do
    echo removing ${name}
    rm -rf info_750_${name}
done
