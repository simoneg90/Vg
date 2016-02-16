#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

for name in ${postfix[@]}
do
    echo building datacard for $name
    dirName="info_750_${name}"
    dcardName="datacard_750_${name}.txt"
    bgLogName="data_${name}_bkg.log"
    sig_norm=`grep 'norm =' ${dirName}/index.html | awk '{print $3}'`    
    bkg_norm=`grep ' Background number of events = ' ${dirName}/${bgLogName} | awk '{print $6}'`
    
    #let's build a datacard!
    cat > ${dirName}/${dcardName} <<EOF
imax 1 number of channels
jmax * number of backgrounds
kmax * number of systematic uncertainty sources
----------
shapes signal     Vg w_signal_750.root          Vg:signal_fixed
shapes background Vg w_background_GaussExp.root Vg:bg
shapes data_obs   Vg w_data.root                Vg:data_obs
----------
## Observation
bin                     Vg
observation             -1
----------
bin                   Vg          Vg
process               signal      background
process               0           1
rate                  ${sig_norm} ${bkg_norm}
cms_lumi_13TeV  lnN   1.046       -     
bg              lnU   -	          2.0
EOF
    
    #now add the systematics to the card
    grep 'sg_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}
    grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
done

