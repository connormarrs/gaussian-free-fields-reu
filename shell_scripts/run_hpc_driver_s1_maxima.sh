#!/bin/bash
#SBATCH --partition=general                          # Name of Partition
#SBATCH --exclude=cn[66-69,71-136,153-256,265-320,325-328]   # make sure we exclude older nodes
#SBATCH --ntasks=156                                  # Request 128 CPU cores
#SBATCH --time=11:30:00                              # Job should run for up to 1.5 hours (for example)
#SBATCH --mail-type=ALL                              # Event(s) that triggers email notification (BEGIN,END,FAIL,ALL)
#SBATCH --mail-user=tyler.campos@yale.edu               # Destination email address