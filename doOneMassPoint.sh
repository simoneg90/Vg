#!/bin/bash
cleanUp=0
rebin=10
debug=0
m=$1
model=$2

./buildInputs.sh $rebin $m $model
./buildDatacards.sh $m
./runLimits.sh $debug $m
