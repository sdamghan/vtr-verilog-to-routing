#!/bin/bash
# Run GA script


################################################
##################--GLOBALS--###################
################################################
footprint=2
DEFAULT_MR=50
DEFAULT_GS=6
DEFAULT_GC=1000

MAX_MR=100
MAX_GS=20
MAX_GC=50000

################################################

TESTS_PATH="./regression_test/benchmark/verilog/ga"
GA_OUTPUTS_DIR="./ga_outputs"
NEW_DIR=""
RUN_PATH=""


################################################
################--FUNCTIONS--###################
################################################
# Init Directories and cleanup
function check_dir () {
	declare -i counter=0;
	while true; 
	do
                if [ -d "${GA_OUTPUTS_DIR}/$(printf "%03d" $counter)"  ]
                then
                        counter=$counter+1;
                else
                        break;
                fi
	done
	NEW_DIR=${GA_OUTPUTS_DIR}/$(printf "%03d" $(($counter-1)))
 }



################################################
##################--MAIN--######################
################################################
#make debug
gcc ./tocsv.c -o tocsv -std=c99

check_dir

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}
        RUN_PATH=${NEW_DIR}/$filename
        
        start=$(date +%s%N)/1000000
        for ((mr=5; mr<=$MAX_MR; mr=mr+5))
        do
            for ((gs=1; gs<=$MAX_GS; gs++))
            do
                for ((gc=1000; gc<=$MAX_GC; gc=gc+500))
                do

                    curr_mr_gs_gc_folder=${RUN_PATH}/MR$mr/GS$gs/GC$gc
                    curr_mr_gs_folder=${RUN_PATH}/MR$mr/GS$gs
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_mr_gs_folder}/csv/overall_$filename-MR_$mr%-GS_$gs-GC_1k-50k.csv

                    curr_mr_folder=${RUN_PATH}/MR$mr
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_mr_folder}/csv/overall_$filename-MR_$mr%-GS_1-20-GC_1k-50k.csv

                    curr_folder=${RUN_PATH}
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_folder}/csv/overall_$filename-MR_5%-100%-GS_1-20-GC_1k-50k.csv

                done                    
            done
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- General CSV Generation"
        printf "\n"

done