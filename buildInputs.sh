#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

rebin=$1
mass=$2

for name in ${postfix[@]}
do
    echo $name
    echo
    echo "root -x -b -l -q Display_SignalFits.cc\(\"${name}\"\,\"\",\"\",\"signal\",${mass},${rebin}\) > signal${mass}_${name}_sig.log"
    echo
    root -x -b -l -q Display_SignalFits.cc\(\"${name}\"\,\"\",\"\",\"signal\",${mass},${rebin}\) > signal${mass}_${name}_sig.log
    echo
    echo "root -x -b -l -q BackgroundPrediction.c\(\"${name}\",${rebin}\) > data_${name}_bkg.log"
    echo
    root -x -b -l -q BackgroundPrediction.c\(\"${name}\",${rebin}\) > data_${name}_bkg.log
    
    # now we put all of our outputs in one place so we can process them later
    cp -r SignalFits info_${mass}_${name}
    cp ${name}_multipdf.root info_${mass}_${name}/
    mv CR_RooFit_Exp_log.pdf info_${mass}_${name}/
    mv CR_RooFit_Exp.pdf info_${mass}_${name}/
    mv signal${mass}_${name}_sig.log info_${mass}_${name}/
    mv data_${name}_bkg.log  info_${mass}_${name}/    

    mv w_data.root info_${mass}_${name}/
    mv w_background_GaussExp.root info_${mass}_${name}/
    mv w_signal_${mass}.root info_${mass}_${name}/
done

