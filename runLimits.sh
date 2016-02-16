#!/bin/bash
for i in 750
do
	echo "mass point $i"
	text2workspace.py vg_$i\.txt  -o vg_$i\.root
	combine -M Asymptotic -v3 vg_$i\.txt -t -1	&> CMS_vg_$i\_13TeV_asymptoticCLs.out
	#combine HbbHbb_$i\.txt -M Asymptotic -v2 -t -1 -m $i -n CMSHH4b --rMax 1000 --rMin 0.01 &> CMS_HH4b_$i\_13TeV_asymptoticCLs.out
	mv higgsCombineCMSvg.Asymptotic.mH$i\.root Limits/CMS_$i\_vg_13TeV_asymptoticCLs.root
	combine -M MaxLikelihoodFit --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out sig vg$i\.txt &> CMS_vg_$i\_13TeV_MaxLikelihood.out
done
