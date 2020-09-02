#!/bin/bash
# Run GA script


################################################################################################
##########################################--GLOBALS--###########################################
################################################################################################
footprint=2
DEFAULT_MR=50
DEFAULT_GS=6
DEFAULT_GC=1000

MIN_MR=10
# MIN_GS=5
# MIN_GC=1000

MAX_MR=100
# MAX_GS=15
# MAX_GC=20000

RATE_MR=10
# RATE_GS=1
# RATE_GC=1000


GS_ARRAY=(1 2 4 8 16)
GS_ARRAY_SIZE=5
GC_ARRAY=(256 512 1024 2048 4096 8192 16384 32768)
GC_ARRAY_SIZE=8

WIDE_PATH="==========================================="

################################################

TESTS_PATH="./regression_test/benchmark/verilog/ga"
GA_OUTPUTS_DIR="./ga_outputs"
NEW_DIR=""
RUN_PATH=""
################################################################################################
########################################--FUNCTIONS--###########################################
################################################################################################
# Init Directories and cleanup

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

################################################################################################
#########################################--CHART CSV--##########################################
################################################################################################
start=$(date +%s%N)/1000000
printf "\n-------------------- Generating general chart.csv files --------------------\n\n"
gcc ./findMinCP.c -o findMinCP -std=c99

check_dir_csv

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}
        RUN_PATH=${NEW_DIR}/$filename
        mkdir -p ${RUN_PATH}/charts
        CHART_PATH=${RUN_PATH}/charts

        ./findMinCP -T ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${GS_ARRAY[0]}-${GS_ARRAY[GS_ARRAY_SIZE-1]}-GC_${GC_ARRAY[0]}k-${GC_ARRAY[GC_ARRAY_SIZE-1]}k.csv $filename > ${CHART_PATH}/db.csv &

        ./findMinCP -C ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${GS_ARRAY[0]}-${GS_ARRAY[GS_ARRAY_SIZE-1]}-GC_${GC_ARRAY[0]}k-${GC_ARRAY[GC_ARRAY_SIZE-1]}k.csv $filename > ${CHART_PATH}/chart_gc.csv &

        ./findMinCP -S ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${GS_ARRAY[0]}-${GS_ARRAY[GS_ARRAY_SIZE-1]}-GC_${GC_ARRAY[0]}k-${GC_ARRAY[GC_ARRAY_SIZE-1]}k.csv $filename > ${CHART_PATH}/chart_gs.csv &

        ./findMinCP -M ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${GS_ARRAY[0]}-${GS_ARRAY[GS_ARRAY_SIZE-1]}-GC_${GC_ARRAY[0]}k-${GC_ARRAY[GC_ARRAY_SIZE-1]}k.csv $filename > ${CHART_PATH}/chart_mr.csv &

        ./findMinCP -G ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${GS_ARRAY[0]}-${GS_ARRAY[GS_ARRAY_SIZE-1]}-GC_${GC_ARRAY[0]}k-${GC_ARRAY[GC_ARRAY_SIZE-1]}k.csv $filename > ${CHART_PATH}/chart.csv 

        wait
done
end=$(date +%s%N)/1000000

printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
echo "[INFO] $filename -- General Chart CSV Generation"
