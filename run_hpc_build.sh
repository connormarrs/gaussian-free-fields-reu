#!/bin/bash
#SBATCH --partition=general                          # Name of Partition
#SBATCH --exclude=cn[66-69,71-136,153-256,265-320,325-328]   # make sure we exclude older nodes
#SBATCH --ntasks=156                                  # Request 128 CPU cores
#SBATCH --time=11:30:00                              # Job should run for up to 1.5 hours (for example)
#SBATCH --mail-type=ALL                              # Event(s) that triggers email notification (BEGIN,END,FAIL,ALL)
#SBATCH --mail-user=cmarrs@bowdoin.edu               # Destination email address

cd ~/gaussian-free-fields-reu/simulations/build/

nvals=($(seq 1660 10 2500))
declare -i iter=0
for i in ${nvals[@]}; do
	./run_driver ${i}&
	if ((iter%25==0));
	then
		wait 
		echo "divisible by 25"
	fi
	echo "$i"
	((iter=iter+1))
done
echo "job done :)"