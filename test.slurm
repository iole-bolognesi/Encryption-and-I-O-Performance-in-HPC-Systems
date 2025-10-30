#!/bin/bash
#SBATCH --job-name=test-job
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --qos=standard
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=3
#SBATCH --partition=standard
#SBATCH --output=%x-%j.out

# Replace [budget code] below with your budget code
#SBATCH --account=[budget code]

module --silent load intel-20.4/compilers

# Change the runtime arguments according to directories you want to compare
DATASET=data # Change this path to point to your local dataset 
OUTPUT=output/decryptedData  # Change this path to point to your output directory

./bin/test "$DATASET" "$OUTPUT"