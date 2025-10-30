# Proof of concept
This README provides instructions to:

- [Compile the proof of concept](#compile-the-poc)
- [Run the proof of concept](#run-the-poc)

## Compile the POC

To compile, use the Makefile provided. <br>
Before doing so, make sure to update the variables `CRYPTO_PATH` and `ADIOS2_PATH` in the Makefile to point to your local installations of Crypto++ and ADIOS 2. After that, run: 

```bash
$ module load intel-20.4/compilers
$ make 
```

## Run the POC
Before running the POC, update the variables `CRYPTO_PATH` and `ADIOS2_PATH` in the slurm script. The former should point to your local installation of Crypto++, the latter should point to the folder "lib64" inside your local installation of ADIOS 2. <br>
After that, run: 

```bash
$ sbatch poc.slurm
```


