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

WIDE_PATH="==========================================="

################################################

TESTS_PATH="./regression_test/benchmark/verilog/ga"
GA_OUTPUTS_DIR="./ga_outputs"
NEW_DIR=""
RUN_PATH=""


################################################
################--FUNCTIONS--###################
################################################
# Init Directories and cleanup
function helpFunction()
{
   echo ""
   echo -e "Specify the default values\n"
   echo "Usage: $0 [-m Mutation Rate (0-100)] [-s Generation Size [1-20]]"
   echo -e "\t[-c Generation Count [1K-100K]]"
   echo ""
   exit 1 # Exit script after printing help
}

function print_config () {
        
        printf "\n$WIDE_PATH\n"
        printf "\t-Mutation rate: %d%%\n\t-Generation size: %d\n\t-Generation count: %d\n" $DEFAULT_MR $DEFAULT_GS $DEFAULT_GC
        printf "$WIDE_PATH\n\n"
}

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
while getopts ":m:s:c:h:" opt;
do
        case "$opt" in

                m) _MR=${OPTARG}
                ;;
                s) _GS=${OPTARG}
                ;;
                c) _GC=${OPTARG}
                ;;
                ?) helpFunction
                ;;
        esac
                
done

if [ -n "$_MR" ]
then
        DEFAULT_MR=$_MR
fi
if [ -n "$_GS" ]
then
        DEFAULT_GS=$_GS
fi
if [ -n "$_GC" ]
then
        DEFAULT_GC=$_GC
fi

print_config

#make debug
gcc ./tocsv.c -o tocsv -std=c99

check_dir
mkdir -p ${NEW_DIR}

printf "\n-------------------- Running Odin-II for test cases! --------------------\n"

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}

        if [ "$filename" == "*" ];
        then
                printf "\n** ERROR: No file exists! **\n\n"
                exit 1
        fi

        mkdir ${NEW_DIR}/$filename
        RUN_PATH=${NEW_DIR}/$filename
        mkdir -p ${RUN_PATH}/csv

        generation_size=$DEFAULT_GS
        generation_count=$DEFAULT_GC
        
        start=$(date +%s%N)/1000000
        for ((mr=5; mr<=$MAX_MR; mr=mr+5))
        do

                ##########################################################
                # fix mutation rate and generation count! increase the generation size by 1 till 20
                mkdir -p ${RUN_PATH}/MR$mr
                curr_mr_folder=${RUN_PATH}/MR$mr
                mkdir -p ${curr_mr_folder}/csv

                start=$(date +%s%N)/1000000
                for ((gs=1; gs<=$MAX_GS; gs++))
                do


                        ##########################################################
                        # fix mutation rate and generation size! increase the generation count by 1000 till 100K
                        mkdir -p ${curr_mr_folder}/GS$gs
                        curr_mr_gs_folder=${curr_mr_folder}/GS$gs
                        mkdir -p ${curr_mr_gs_folder}/csv

                        start=$(date +%s%N)/1000000
                        for ((gc=1000; gc<=$MAX_GC; gc=gc+500))
                        do

                                mkdir -p ${curr_mr_gs_folder}/GC$gc
                                curr_mr_gs_gc_folder=${curr_mr_gs_folder}/GC$gc
                                mkdir -p ${curr_mr_gs_gc_folder}/csv
                        
                                ./odin_II -V $file --GA $footprint --GA-MR $mr --GA-GS $gs --GA-GC $gc > ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out &&
                                ./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out > ${curr_mr_gs_gc_folder}/csv/$filename-MR_$mr%-GS_$gs-GC_$gc.csv &
                        done
                        end=$(date +%s%N)/1000000

                        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
                        echo "$filename -- Generation Count Changing:"
                        ls ${curr_mr_gs_gc_folder}/
                        printf "\n\n"

                done
                end=$(date +%s%N)/1000000

                printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
                echo "$filename -- Generation Size Changing:"
                ls ${curr_mr_gs_folder}/
                printf "\n"
        wait
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- Mutation Rate Changing:" 
        ls ${curr_mr_folder}/
        printf "\n"
done


printf "\n-------------------- Generating general csv files --------------------\n\n"
./tocsv_script2.sh
