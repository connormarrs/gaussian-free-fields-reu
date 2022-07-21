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

# purge old modules and load good ones
module purge
module load gcc/9.2.0 cmake/3.10.2

export LD_LIBRARY_PATH=/usr/lib

fileNames="../src/DFGF_S1.cpp ../src/DFGF_T2.cpp ../src/driver.cpp ../src/RandVec.cpp ../src/RandArr.cpp ../src/tools.cpp" 

# binaryName="~/gaussian-free-fields/simulations/build/run_driver"
cd simulations/build/

g++ -std=c++11 -pthread -static-libstdc++ -Wall $fileNames -o run_driver && echo "compilation successful"

# ./run_driver
