#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

for name in ${postfix[@]}
do
    echo running asymptotic limits for $name
    dirName="info_750_${name}"    
    dcardName="datacard_750_${name}"
    logName="asymp_750_${name}.log"

    pushd $dirName > /dev/null
    text2workspace.py ${dcardName}.txt -o ${dcardName}.root >& /dev/null
    combine -M Asymptotic ${dcardName}.txt -t -1 --rMax 2.0 | tee ${logName}
    popd > /dev/null
done

