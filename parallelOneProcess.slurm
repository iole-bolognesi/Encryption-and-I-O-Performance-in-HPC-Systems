#!/bin/bash
#SBATCH --job-name=parallel-job
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
module --silent load intel-20.4/mpi

# !!! IMPORTANT !!!
# Change this path to point to your local installations of Crypto++ 
CRYPTO_PATH=./cryptopp-master

# !!! IMPORTANT !!!
# Change this path to point to "lib64" of the ADIOS 2 installation path, 
# example: adios2-install-directory/lib64
ADIOS2_PATH=./adios2-install-bugfix/lib64

export LD_LIBRARY_PATH="$CRYPTO_PATH:$ADIOS2_PATH:$LD_LIBRARY_PATH"

# Change the runtime arguments according to the experiment you want to run
DATASET=data # Change this path to point to your local dataset 
ALGORITHM=AES_ECB   # Change the algorithm and mode combination as <ALGORITHM_MODE>

srun --unbuffered --distribution=block:block --hint=nomultithread ./bin/parallel "$DATASET" "$ALGORITHM"