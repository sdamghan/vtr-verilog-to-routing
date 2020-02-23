#!/bin/bash
# Run GA script


################################################
##################--GLOBALS--###################
################################################
footprint=2
DEFAULT_MR=50
DEFAULT_GS=2
DEFAULT_GC=1

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
	NEW_DIR=${GA_OUTPUTS_DIR}/$(printf "%03d" $counter)
 }



################################################
##################--MAIN--######################
################################################
#make debug

check_dir
mkdir -p ${NEW_DIR}

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}
        mkdir ${NEW_DIR}/$filename
        RUN_PATH=${NEW_DIR}/$filename

        mkdir ${RUN_PATH}/mutation_rate_changing
        generation_size=$DEFAULT_GS
        generation_count=$DEFAULT_GC
        start=$(date +%s%N)/1000000
        for ((mr=5; mr<=100; mr=mr+5))
        do
                ./odin_II -V $file --GA $footprint --GA-MR $mr --GA-GS $generation_size --GA-GC $generation_count > ${RUN_PATH}/mutation_rate_changing/$filename-MR_$mr%-GS_$generation_size-GC_$generation_count.out
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- Mutation Rate Changing:" 
        ls ${RUN_PATH}/mutation_rate_changing/
        printf "\n"


        ##########################################################
        # fix mutation rate and generation count! increase the generation size by 1 till 20
        mkdir ${RUN_PATH}/generation_size_changing
        mutation_rate=$DEFAULT_MR
        generation_count=$DEFAULT_GC
        start=$(date +%s%N)/1000000
        for ((gs=1; gs<=20; gs++))
        do
                ./odin_II -V $file --GA $footprint --GA-MR $mutation_rate --GA-GS $gs --GA-GC $generation_count > ${RUN_PATH}/generation_size_changing/$filename-MR_$mutation_rate%-GS_$gs-GC_$generation_count.out
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- Generation Size Changing:"
        ls ${RUN_PATH}/generation_size_changing/
        printf "\n"


        ##########################################################
        # fix mutation rate and generation size! increase the generation count by 1000 till 100K
        mkdir ${RUN_PATH}/generation_count_changing
        mutation_rate=$DEFAULT_MR
        generation_size=$DEFAULT_GS
        start=$(date +%s%N)/1000000
        for ((gc=10; gc<=100; gc=gc+10))
        do
                ./odin_II -V $file --GA $footprint --GA-MR $mutation_rate --GA-GS $generation_size --GA-GC $gc > ${RUN_PATH}/generation_count_changing/$filename-MR_$mutation_rate%-GS_$generation_size-GC_$gc.out
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- Generation Count Changing:"
        ls ${RUN_PATH}/generation_count_changing/
        printf "\n\n"

done