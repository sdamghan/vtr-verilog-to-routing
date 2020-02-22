#!/bin/bash
# Run GA script

declare -i footprint=2
declare -i mutation_rate_percentage=50
declare -i generation_size=6
declare -i generation_count=32

#make debug

for (( c=1; c<=5; c++ ))
do
	./odin_II -V ../vtr_flow/benchmarks/verilog/mkSMAdapter4B.v --GA $footprint --GA-MR $((mutation_rate_percentage/100)) --GA-GS $generation_size --GA-GC $generation_count > ./GA_outputs/mkSMAdapter4B_MR$((mutation_rate_percentage/100))_GS$((generation_size))_GC$((generation_count))_N$((c)).out
done

