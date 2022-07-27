#!/bin/bash
#SBATCH --partition=general                          # Name of Partition
#SBATCH --exclude=cn[66-69,71-136,153-256,265-320,325-328]   # make sure we exclude older nodes
#SBATCH --ntasks=156                                  # Request 128 CPU cores
#SBATCH --time=11:30:00                              # Job should run for up to 1.5 hours (for example)
#SBATCH --mail-type=ALL                              # Event(s) that triggers email notification (BEGIN,END,FAIL,ALL)
#SBATCH --mail-user=tyler.campos@yale.edu               # Destination email address
cd simulations/build
nvals=(1000 10000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000)
#nvals=(1000 2000 3000 4000 5000 6000)
declare -i iter=0
for i in ${nvals[@]}; do
	./run_driver_s1_trial_data ${i}
done
echo "job done :)"