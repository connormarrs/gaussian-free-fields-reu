#!/bin/bash
#SBATCH --partition=debug                     # Name of Partition
#SBATCH --ntasks=4                            # Maximum CPU cores for job
#SBATCH --nodes=1                             # Ensure all cores are from the same node
#SBATCH --time=5                              # Job should run for up to 5 minutes (for example)
#SBATCH --exclude=cn[66-69,71-136,155-314,325-328] # make sure we exclude older nodes
#                       # Event(s) that triggers email notification (BEGIN,END,FAIL,ALL)
#SBATCH --mail-user=cmarrs@bowdoin.edu      # Destination email address

# scratch and shared files
# /scratch/lur07001/com22009/

cd ~/gaussian-free-fields-reu/simulations/vcpkg/
# ./bootstrap-vcpkg.sh -disableMetrics
./vcpkg integrate install
./vcpkg install jsoncpp

# cd ~/gaussian-free-fields-reu/simulations/build/
# cmake .. && make

# ./run_driver
