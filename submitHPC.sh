	#!/bin/bash

	function usage() {
	    echo "sh SubmitCMSSW.sh <massMin> <massMax> <stepSize> <model[0_9]> <Output>"
	    exit;
    }

	if [ ! -n "$1" ] || [ ! -n "$2" ]  || [ ! -n "$3" ] || [ ! -n "$4" ] || [ ! -n "$5" ] ; then usage; fi;

    model=$4
	OUTPUT=$5
	mkdir -p $OUTPUT
	mkdir -p ${OUTPUT}/logs
	mkdir -p ${OUTPUT}/errs

	echo "Output will be stored to : $OUTPUT"
	echo "LogFiles will be stored to : $OUTPUT/logs"

    JOB=1
    for i in `seq $1 $3 $2`;
    do

    mass=$i

	echo "#!/bin/bash              
	#
	#PBS -r n 
	##Job settings                                                                                                                                                                       
	#PBS -N ROOT                                                                                                                                                                       
	#PBS -o ${OUTPUT}/HPCLogs_${JOB}.txt
	#PBS -e ${OUTPUT}/HPCErrors_${JOB}.txt

	##Job Configuration                                                                                                                                                                  
	##Job Resources                                                                                                                                                                   
	#PBS -l walltime=00:04:00:00 
	#PBS -l nodes=1:ppn=1                                                                                                                                                                
	#PBS -l pmem=3000mb              
	# initialize environment for worker
	BASE=/scratch/osg/lesya/CMSSW_7_1_5/src/VgHPC
	cd \$BASE

	export SCRAM_ARCH=slc6_amd64_gcc481/
	export OSG_APP=/osg/app
	export VO_CMS_SW_DIR=\${OSG_APP}/cmssoft/cms
	export CMS_PATH=\${VO_CMS_SW_DIR}
	. ${CMS_PATH}/cmsset_default.sh;
	eval \`scramv1 runtime -sh\`


	cd \$BASE
	export LD_LIBRARY_PATH=\"/osg/app/cmssoft/cms/osg/app/GLITE/GLITE_3_2_7-0/d-cache/dcap/lib:$LD_LIBRARY_PATH\";

	# enter working area

	./doOneMassPoint.sh ${mass} ${model} > ${OUTPUT}/logs/Job_${JOB}.txt 2>  ${OUTPUT}/errs/Job_${JOB}.txt
	" > submit.sh ;


    qsub submit.sh;
    JOB=`expr $JOB + 1`

    done


