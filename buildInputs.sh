#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

for name in ${postfix[@]}
do
    echo $name
    echo
    echo "root -x -b -l -q Display_SignalFits.cc\(\"${name}.root\"\,\"\",\"\",\"signal750_\",10\) > signal750_${name}_sig.log"
    echo
    root -x -b -l -q Display_SignalFits.cc\(\"${name}.root\"\,\"\",\"\",\"signal750_\",10\) > signal750_${name}_sig.log
    echo
    echo "root -x -b -l -q BackgroundPrediction.c\(\"data_${name}.root\",10\) > data_${name}_bkg.log"
    echo
    root -x -b -l -q BackgroundPrediction.c\(\"data_${name}.root\",10\) > data_${name}_bkg.log
    
    # now we put all of our outputs in one place so we can process them later
    cp -r SignalFits info_750_${name}
    mv CR_RooFit_Exp_log.pdf info_750_${name}/
    mv CR_RooFit_Exp.pdf info_750_${name}/
    mv signal750_${name}_sig.log info_750_${name}/
    mv data_${name}_bkg.log  info_750_${name}/    

    mv w_data.root info_750_${name}/
    mv w_background_GaussExp.root info_750_${name}/
    mv w_signal_750.root info_750_${name}/
done

