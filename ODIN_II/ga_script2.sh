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
MIN_GS=5
MIN_GC=1000

MAX_MR=100
MAX_GS=15
MAX_GC=20000

RATE_MR=10
RATE_GS=1
RATE_GC=1000

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
        printf "[INFO] Default Values\n\t- Mutation rate: %d%%\n\t- Generation size: %d\n\t- Generation count: %d\n" $DEFAULT_MR $DEFAULT_GS $DEFAULT_GC
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
###########################################--MAIN--#############################################
############################################--GA--##############################################
################################################################################################
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
                printf "\n[INFO] ** ERROR: No file exists! **\n\n"
                exit 1
        fi

        mkdir ${NEW_DIR}/$filename
        RUN_PATH=${NEW_DIR}/$filename
        mkdir -p ${RUN_PATH}/csv

        generation_size=$DEFAULT_GS
        generation_count=$DEFAULT_GC
        
        start=$(date +%s%N)/1000000
        for ((mr=$MIN_MR; mr<=$MAX_MR; mr=mr+$RATE_MR))
        do
                ##########################################################
                # fix mutation rate and generation count! increase the generation size by 1 till 20
                mkdir -p ${RUN_PATH}/MR$mr
                curr_mr_folder=${RUN_PATH}/MR$mr
                mkdir -p ${curr_mr_folder}/csv

                start=$(date +%s%N)/1000000
                for ((gs=$MIN_GS; gs<=$MAX_GS; gs=gs+$RATE_GS))
                do
                        ##########################################################
                        # fix mutation rate and generation size! increase the generation count by 1000 till 100K
                        mkdir -p ${curr_mr_folder}/GS$gs
                        curr_mr_gs_folder=${curr_mr_folder}/GS$gs
                        mkdir -p ${curr_mr_gs_folder}/csv

                        start=$(date +%s%N)/1000000
                        for ((gc=$MIN_GC; gc<=$MAX_GC; gc=gc+$RATE_GC))
                        do

                                mkdir -p ${curr_mr_gs_folder}/GC$gc
                                curr_mr_gs_gc_folder=${curr_mr_gs_folder}/GC$gc
                                mkdir -p ${curr_mr_gs_gc_folder}/csv
                        
                                ./odin_II -V $file --GA $footprint --GA-MR $mr --GA-GS $gs --GA-GC $gc > ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out &&
                                ./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out > ${curr_mr_gs_gc_folder}/csv/$filename-MR_$mr%-GS_$gs-GC_$gc.csv &
                        done
                        end=$(date +%s%N)/1000000

                        printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
                        echo "$filename MR:$mr GS:$gs -- Generation Count Changing:"
                        ls ${curr_mr_gs_gc_folder}/
                        printf "\n\n"
                wait   
                done
                end=$(date +%s%N)/1000000

                printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
                echo "$filename MR:$mr -- Generation Size Changing:"
                ls ${curr_mr_gs_folder}/
                printf "\n"
        # wait
        done
        end=$(date +%s%N)/1000000

        printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "$filename -- Mutation Rate Changing:" 
        ls ${curr_mr_folder}/
        printf "\n"
done


################################################################################################
############################################--CSV--#############################################
################################################################################################
printf "\n-------------------- Generating general csv files --------------------\n\n"
check_dir_csv

for file in ${TESTS_PATH}/*.v;
do
        no_path=${file##*/}
        filename=${no_path%.*}
        RUN_PATH=${NEW_DIR}/$filename
        
        start=$(date +%s%N)/1000000
        for ((mr=$MIN_MR; mr<=$MAX_MR; mr=mr+$RATE_MR))
        do
            start=$(date +%s%N)/1000000
            for ((gs=$MIN_GS; gs<=$MAX_GS; gs=gs+$RATE_GS))
            do
                start=$(date +%s%N)/1000000
                for ((gc=$MIN_GC; gc<=$MAX_GC; gc=gc+$RATE_GC))
                do

                    curr_mr_gs_gc_folder=${RUN_PATH}/MR$mr/GS$gs/GC$gc
                    curr_mr_gs_folder=${RUN_PATH}/MR$mr/GS$gs
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_mr_gs_folder}/csv/overall_$filename-MR_$mr%-GS_$gs-GC_${MIN_GC}k-${MAX_GC}k.csv &

                    curr_mr_folder=${RUN_PATH}/MR$mr
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_mr_folder}/csv/overall_$filename-MR_$mr%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv &

                    curr_folder=${RUN_PATH}
                    (./tocsv ${curr_mr_gs_gc_folder}/$filename-MR_$mr%-GS_$gs-GC_$gc.out && printf "\n\n") >> ${curr_folder}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv &

                    wait            
                done
                end=$(date +%s%N)/1000000
                printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
                echo "[INFO] MR:$mr GS:$gs -- General CSV Generation"
                printf "\n"                  
            done
            end=$(date +%s%N)/1000000
            printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
            echo "[INFO] MR:$mr --DONE-- General CSV Generation"
            printf "\n"
        done
        end=$(date +%s%N)/1000000

        printf "Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
        echo "[INFO] $filename -- General CSV Generation"
        printf "\n"

done



################################################################################################
#########################################--CHART CSV--##########################################
################################################################################################
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

        ./findTopFitnesses -T ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv $filename > ${CHART_PATH}/db.csv &

        ./findTopFitnesses -C ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv $filename > ${CHART_PATH}/chart_gc.csv &

        ./findTopFitnesses -S ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv $filename > ${CHART_PATH}/chart_gs.csv &

        ./findTopFitnesses -M ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv $filename > ${CHART_PATH}/chart_mr.csv &

        ./findTopFitnesses -G ${RUN_PATH}/csv/overall_$filename-MR_${MIN_MR}%-${MAX_MR}%-GS_${MIN_GS}-${MAX_GS}-GC_${MIN_GC}k-${MAX_GC}k.csv $filename > ${CHART_PATH}/chart.csv 

        wait
done
end=$(date +%s%N)/1000000

printf "[INFO] Execution time: %.3f s\n" $(bc <<<"scale=4;$[end-start]/1000")
echo "[INFO] $filename -- General Chart CSV Generation"
