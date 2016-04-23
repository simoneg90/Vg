#!/bin/bash
cleanUp=0
rebin=10
debug=0
m=$1

./buildInputs.sh $rebin $m 0
./buildDatacards.sh $m
./runLimits.sh $debug $m
