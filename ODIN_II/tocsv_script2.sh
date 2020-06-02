#!/bin/bash

TESTS_PATH="./regression_test/benchmark/verilog/ga"
GA_OUTPUTS_DIR="./ga_outputs"
NEW_DIR=""
RUN_PATH=""


MIN_MR=10
MIN_GS=5
MIN_GC=1000

MAX_MR=100
MAX_GS=20
MAX_GC=20000

RATE_MR=10
RATE_GS=1
RATE_GC=500


# Init Directories and cleanup
 function check_dir_csv () {
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

start=$(date +%s%N)/1000000
printf "\n-------------------- Generating general chart.csv files --------------------\n\n"
gcc ./findTopFitnesses.c -o findTopFitnesses -std=c99

check_dir_csv

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}
        RUN_PATH=${NEW_DIR}/$filename
        mkdir -p ${RUN_PATH}/charts
        CHART_PATH=${RUN_PATH}/charts

        ./findTopFitnesses -C ${RUN_PATH}/csv/overall_$filename-MR_5%-100%-GS_1-20-GC_1k-50k.csv > ${CHART_PATH}/chart_gc.csv &

        ./findTopFitnesses -S ${RUN_PATH}/csv/overall_$filename-MR_5%-100%-GS_1-20-GC_1k-50k.csv > ${CHART_PATH}/chart_gs.csv &

        ./findTopFitnesses -M ${RUN_PATH}/csv/overall_$filename-MR_5%-100%-GS_1-20-GC_1k-50k.csv > ${CHART_PATH}/chart_mr.csv &

        ./findTopFitnesses -G ${RUN_PATH}/csv/overall_$filename-MR_5%-100%-GS_1-20-GC_1k-50k.csv > ${CHART_PATH}/chart.csv 

        wait
done
end=$(date +%s%N)/1000000

printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
echo "[INFO] $filename -- General Chart CSV Generation"
