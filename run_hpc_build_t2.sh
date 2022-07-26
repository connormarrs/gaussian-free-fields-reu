#!/bin/bash
#SBATCH --partition=general                          # Name of Partition
#SBATCH --exclude=cn[66-69,71-136,153-256,265-320,325-328]   # make sure we exclude older nodes
#SBATCH --ntasks=156                                  # Request 128 CPU cores
#SBATCH --time=11:30:00                              # Job should run for up to 1.5 hours (for example)
#SBATCH --mail-type=ALL                              # Event(s) that triggers email notification (BEGIN,END,FAIL,ALL)
#SBATCH --mail-user=tyler.campos@yale.edu               # Destination email address

cd ~/gaussian-free-fields-reu/simulations/build/

nvals=($(seq 500 10 10000))
declare -i iter=0
for i in ${nvals[@]}; do
	./run_driver_T2 ${i}&
	if ((iter%64==0));
	then
		wait
		echo "divisible by 64"
	fi
	echo "$i"
	((iter=iter+1))
done
echo "job done :)"

