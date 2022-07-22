#!/bin/bash
# declare -i n_start=500
# declare -i size_n_incr=100
# declare -i n_incr=10

# counter_vals=($(seq 0 1 100))

# for (( batch_nval=start; batch_nval<=; batch_nval+= )) do
# 	for (( small_counter=)) do
# 		echo "running driver with n=${i}"
# 		# ./run_driver ${i} &
# 	done
# 	wait
# done

nvals=($(seq 500 10 2500))
for i in ${nvals[@]}; do
	./run_driver ${i} &
done

echo "job done :)"

