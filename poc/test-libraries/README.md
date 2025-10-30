# Proof of concept
This README provides instructions to:

- [Compile the test scripts](#compile-the-test-scripts)
- [Run the test scripts](#run-the-test-scripts)

## Compile the test scripts

Before running,  update the variable `CRYPTO_PATH`to point to your local installation of Crypto++. 
After that, run:

```bash
$ module load intel-20.4/compilers
$ make 
```

## Run the test scripts
Before running,  update the variable `CRYPTO_PATH`to point to your local installation of Crypto++ and uncomment the correct command based on the script you want to run. 
After that, run: 


```bash
$ sbatch libtest.slurm
```