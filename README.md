# Encryption and I/O Performance in HPC Systems 
This is a MSc dissertation project at the University of Edinburgh under supervision of [Linnea Gilius](https://www.epcc.ed.ac.uk/about-us/our-team/linnea-gilius).

## MSc Project Details	
Author(s): Iole Bolognesi <br>
Supervisor: [Linnea Gilius](https://www.epcc.ed.ac.uk/about-us/our-team/linnea-gilius) <br>
Organisation: [EPCC - The University of Edinburgh](https://www.epcc.ed.ac.uk/) <br>
Topic: This project investigates the performance of encryption and I/O operations for large-scale datasets in HPC systems.  

## Description of contents 
The proof of concept and the testing of libraries are included in this branch. This section points to the exact folders and subfolders. <br>
[Proof-of-Concept](https://github.com/iole-bolognesi/Encryption-and-I-O-Performance-in-HPC-Systems/tree/main/poc): Implementation of AES in CBC mode using [Crypto++](https://github.com/weidai11/cryptopp) integrated with [ADIOS 2](https://adios2.readthedocs.io/en/v2.10.2/) <br>
[Testing of Libraries](https://github.com/iole-bolognesi/Encryption-and-I-O-Performance-in-HPC-Systems/tree/main/poc/test-libraries): Implementation of AES in CBC mode using different libraries <br>


## Important Note on Dataset 
The experiments conducted and reported in the dissertation report cannot be replicated because the dataset used ([CPSea](https://www.kaggle.com/datasets/ziyiyang180104/cpsea)) was updated on 8 August 2025 and the previous version is not accessible anymore. Although we retain a copy of the dataset, it will not be shared entirely as the license does not provide clear instructions on the copyright of previous dataset versions. We are searching for a replacement dataset. In the meantime, in order to allow code runs, a minor section of the dataset used was pushed to this repository, in the [data]([https://git.ecdf.ed.ac.uk/msc-24-25/s2759018/-/tree/main/data?ref_type=heads](https://github.com/iole-bolognesi/Encryption-and-I-O-Performance-in-HPC-Systems/tree/main/data)) folder. <br>

## Ethics Assessment 

Question: Are you working with data that requires special data handling or consent? <br>
Answer: No <br>
Question: Are you working with human participants? <br>
Answer: No <br>
Question: Are you working with animals? <br>
Answer: No <br>
Question: Does your research involve developing countries?<br>
Answer: No <br>
Question: Does your research have the potential for dual use?<br>
Answer: No <br>
Question: Does your research concern groups which may be construed as terrorist or extremist?<br>
Answer: No <br>

## Code
### Serial Pipeline
The serial pipeline encrypts, stores, retrieves, and decrypts a dataset serially.  Each file is encrypted and the resulting binary cipher-text is appended to a single buffer. During encryption, metadata is generated for each file. The complete dataset cipher-text and the corresponding metadata are then written to disk. Finally, these are read back and, using the metadata to locate file boundaries,
the cipher-text of the dataset is decrypted back into individual files. <br> 

Serial experiments were conducted with the following combinations of ciphers and encryption modes:

| Cipher   | Modes                          |
|----------|--------------------------------|
| AES      | CBC, ECB, CFB, OFB, CTR        |
| Serpent  | CBC, ECB, CFB, OFB, CTR        |
| Twofish  | CBC, ECB, CFB, OFB, CTR        |
| RC6      | CBC, ECB, CFB, OFB, CTR        |
| MARS     | CBC, ECB, CFB, OFB, CTR        |
| ChaCha20 | Not Applicable                 |

### Parallel Pipeline
The parallel pipeline encrypts, stores, retrieves, and decrypts a dataset in parallel using MPI and [ADIOS 2](https://adios2.readthedocs.io/en/v2.10.2/)
for parallel I/O operations. <br>. The dataset files are first distributed evenly across MPI processes. Then, the dataset is encrypted as each process iterates through its local dataset partition: each file is encrypted and the resulting binary cipher-text is appended to a single local cipher-text buffer. During encryption, metadata is generated for each file. The local cipher-texts and the corresponding metadata are written to disk in parallel through ADIOS 2. Finally, these are read back through ADIOS 2, and, using the local metadata to locate file boundaries, each process decrypts their local cipher-texts  back into individual files. 

Parallel strong scaling and weak scaling experiments were conducted for AES in OFB mode. 


## Instructions 

This README provides instructions to:

- [Build and install ADIOS 2 on Cirrus](#build-and-install-adios2-on-cirrus)
- [Build and install Crypto++](#build-and-install-cryptopp)
- [Compile the code](#compile-the--code)
- [Run the code](#run-the--code)

---

### Build and Install ADIOS2 on Cirrus

```bash
$ module load intel-20.4/compilers
$ module load intel-20.4/mpi
$ module load cmake
$ git clone https://github.com/ornladios/ADIOS2.git ADIOS2
$ mkdir adios2-install
$ mkdir adios2-build && cd adios2-build
$ cmake ../ADIOS2 -DCMAKE_C_COMPILER=mpiicc -DCMAKE_CXX_COMPILER=mpiicpc -DCMAKE_Fortran_COMPILER=mpiifort -DADIOS2_BUILD_EXAMPLES=ON -DADIOS2_USE_MPI=ON
$ make -j 16
$ cmake ../ADIOS2 -DCMAKE_INSTALL_PREFIX=../adios2-install
$ make install
```
### Build and Install CryptoPP
```bash
$ module load intel-20.4/compilers
$ git clone https://github.com/weidai11/cryptopp.git cryptopp-master
$ cd cryptopp-master
$ make
```

### Compile the Code 
To compile, use the Makefile provided. <br>
Before doing so, make sure to update the variables `CRYPTO_PATH` and `ADIOS2_PATH` in the Makefile to point to your local installations of Crypto++ and ADIOS 2. After that, run: 

```bash
$ module load intel-20.4/compilers
$ module load intel-20.4/mpi
$ make 
```

### Run the Code 
Before running any script, update the budget code within the slurm script.  

#### Experiments 
Before running any experiment, update the variables `CRYPTO_PATH` and `ADIOS2_PATH` in the slurm script. The former should point to your local installation of Crypto++, the latter should point to the folder "lib64" inside your local installation of ADIOS 2. <br>
If required, change the `DATASET` variable to point to the dataset to be encrypted (by default, this is `data`), and the `ALGORITHM` variable to use the desired combination of cipher and mode, out of the ones in the [supported ciphers table](#serial-pipeline).

- Use **serial.slurm** script to run all serial experiments. 
- Use **parallelOneProcess.slurm** to run the parallel experiments with a single MPI process. There is a separate script for this because a greater number of CPUs per process is required. 
- Use **parallel2Processes.slurm** to run the parallel experiments with 2 MPI processes. There is a separate script for this because a greater number of CPUs per process is required. 
- Use **parallelOneNode.slurm** to run the parallel experiments with 4-32 MPI processes.
- Use **parallel2Nodes.slurm** to run the parallel experiments with 64 MPI processes.
- Use **parallel3Nodes.slurm** to run the parallel experiments with 89 MPI processes. This was used for weak scaling experiments as the total size of the dataset used was of 89 GB.
- Use **parallel4Nodes.slurm** to run the parallel experiments with 128 MPI processes. This was used for strong scaling experiments only with a dataset partition of 5.2 GB. 
- Use **parallel8Nodes.slurm** to run the parallel experiments with 256 MPI processes. This was used for strong scaling experiments only with a dataset partition of 5.2 GB.

#### Testing 
Correctness is tested by comparing two data directories given as command-line arguments to the test script. <br>
The test script is used to verify that all files within the original dataset directory match the output files in the decrypted dataset directory produced by the serial/parallel code. <br>

If required, change the `DATASET` variable to point to the dataset directory (by default, this is `data`) and the `OUTPUT` variable to point to the decrypted files inside the output directory (by default, this is `output/decryptedData`).
For weak scaling experiments, the maximum running time of the job was changed to 30 hours. 

- Use **test.slurm** script to test correctness. 

