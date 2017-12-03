#!/bin/bash
declare -a array_data=("59" "154" "256" "1379" "1601")
#declare -a array_data=("59")
declare -a array_nth=("1" "2" "4" "8" "10" "15" "20" "30" "40")
for data in "${array_data[@]}"
do
	for nth in "${array_nth[@]}"
	do
    	echo "----Relizando teste com entrada "$data " e com " $nth " nthreads ";
		(time ./trab $data $nth 0) &> saida/saida_data_.$data._thread_.$nth.txt;
	done
done