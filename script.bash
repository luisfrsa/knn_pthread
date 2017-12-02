#!/bin/bash
#declare -a array_data=("59" "154" "256")
declare -a array_data=("59")
declare -a array_nth=("1" "2" "4" "8" "10" "15" "20" "30" "40" "50")
for data in "${array_data[@]}"
do
	for nth in "${array_nth[@]}"
	do
		(time ./trab $data $nth 0) &> saida_$data_$nth.txt
	done
done