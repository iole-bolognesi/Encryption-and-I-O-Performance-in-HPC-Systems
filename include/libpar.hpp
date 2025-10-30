/**
 * @file libpar.hpp
 * @brief This module declares a parallel library
 * @author Iole Bolognesi
 *
 * This module declares the ParallelCTMeta struct and functions that wrap MPI 
 * routines with the aim to separate MPI code from the main code. 
 **/

#ifndef INCLUDE_LIBPAR_HEADER
#define INCLUDE_LIBPAR_HEADER

#include <mpi.h>
#include <adios2.h>
#include "fileIO.hpp"


/* Structure of metadata for local cipher-texts in the parallel pipeline */
struct ParallelCTMeta {
    size_t local_size;
    size_t global_offset;
    std::vector<size_t> files_sizes;
    std::vector<size_t> files_offsets;
};

adios2::ADIOS initParallelContext(int &argc, char ** &argv, int &rank, int &size);
void reduce_and_broadcast(const void *send_buffer, void *recv_buffer, int count,
                  MPI_Datatype datatype, MPI_Op operation, MPI_Comm comm);
void exclusive_scan(const void *send_buffer, void *recv_buffer, int count,
                  MPI_Datatype datatype, MPI_Op operation, MPI_Comm comm);
void waitForProcesses(void);
double getTime(void);
void exitParallelContext(void);
void endParallelContext(void);
void decompose1D(size_t global_size, size_t &offset, size_t &local_size, int nproc, int rank);
#endif 