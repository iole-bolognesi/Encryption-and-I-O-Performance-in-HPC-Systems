#!/bin/bash
#SBATCH --job-name=lib-test-job
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --qos=standard
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --partition=standard
#SBATCH --output=%x-%j.out

# Replace [budget code] below with your budget code
#SBATCH --account=[budget code]

module --silent load intel-20.4/compilers
module load python

# !!! IMPORTANT !!!
# Change this path to point to your local installations of Crypto++ 
CRYPTO_PATH=./../../cryptopp-master

export LD_LIBRARY_PATH="$CRYPTO_PATH:$LD_LIBRARY_PATH"
 
# !!! IMPORTANT !!!
# Uncomment the test script you wish to run

# ./bin/aes_cryptopp
# ./bin/aes_openssl
# python ./python/AES.py