#!/bin/bash
cleanUp=0
rebin=10
debug=0
m=$1
model=$2

models=(
    "env_pdf_0_13TeV_dijet2" "env_pdf_0_13TeV_exp1" "env_pdf_0_13TeV_expow1" "env_pdf_0_13TeV_expow2" "env_pdf_0_13TeV_pow1" "env_pdf_0_13TeV_lau1" "env_pdf_0_13TeV_atlas1" "env_pdf_0_13TeV_atlas2" "env_pdf_0_13TeV_vvdijet1"
)


./buildInputs.sh $rebin $m $model
./buildDatacards_alt.sh $m
./buildDatacards.sh $m

echo "datacard_qqg_${m}_combined_alt.txt"

combine datacard_qqg_${m}_combined_alt.txt -M GenerateOnly -m $m -t 1000  --saveToys -s 334455 --expectSignal=0 -n biasTest
combine datacard_qqg_${m}_combined.txt -M MaxLikelihoodFit -m $m --expectSignal=0 --noErrors --minos none --rMin=-4 --rMax=4 -t 1000 --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.334455.root -s 334455 -n output${m}

