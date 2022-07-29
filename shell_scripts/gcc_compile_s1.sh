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

fileNames1="../src/DFGF_S1.cpp ../src/DFGF_T2.cpp ../src/driver_s1_trial_data.cpp ../src/RandVec.cpp ../src/RandArr.cpp ../src/tools.cpp" 
fileNames2="../src/DFGF_S1.cpp ../src/DFGF_T2.cpp ../src/driver_s1_maxima.cpp ../src/RandVec.cpp ../src/RandArr.cpp ../src/tools.cpp" 
fileNames3="../src/DFGF_S1.cpp ../src/DFGF_T2.cpp ../src/driver_s1_maxima_vector.cpp ../src/RandVec.cpp ../src/RandArr.cpp ../src/tools.cpp"
fileNames4="../src/DFGF_S1.cpp ../src/DFGF_T2.cpp ../src/driver_theoretical_checks.cpp ../src/RandVec.cpp ../src/RandArr.cpp ../src/tools.cpp"  
# binaryName="~/gaussian-free-fields/simulations/build/run_driver"
cd ../simulations/build/

#g++ -std=c++11 -pthread -static-libstdc++ -Wall $fileNames1 -o run_driver_s1_trial_data && echo "compilation successful: trial data"
#g++ -std=c++11 -pthread -static-libstdc++ -Wall $fileNames2 -o run_driver_s1_maxima && echo "compilation successful: maxima"
#g++ -std=c++11 -pthread -static-libstdc++ -Wall $fileNames3 -o run_driver_s1_maxima_vector && echo "compilation successful: maxima_vector"
g++ -std=c++11 -pthread -static-libstdc++ -Wall $fileNames4 -o run_driver_s1_theoretical_checks && echo "compilation successful: theoretical checks"
# ./run_driver
