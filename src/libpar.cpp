/**
 * @file libpar.cpp
 * @brief This modules is a parallel library that serves the purpose to
 * separate MPI code from the main code (serialPipeline.cpp and parallelPipeline.cpp)
 * @author Iole Bolognesi
 * This module provides functions that wrap MPI routines used in the main code. 
 */

#include "libpar.hpp"

/**
 * @brief Initializes MPI and create an ADIOS 2 parallel context. 
 *
 * This functions initializes MPI, sets the MPI rank, and the MPI world size.
 * It also creates and returns an ADIOS object initialized with  MPI_COMM_WORLD
 *
 * @param argc  Refrence to command-line arguments' count  
 * @param argv  Reference to command-line arguments'vector  
 * @param rank  Reference to the rank of the calling process.
 * @param size  Reference to the MPI world size. 
 *
 * @return An ADIOS2 context initialized with MPI_COMM_WORLD.
 */
adios2::ADIOS initParallelContext(int &argc, char ** &argv, int &rank, int &size) {
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    adios2::ADIOS adios(MPI_COMM_WORLD);
    return adios;
}

/**
 * @brief Performs MPI_Allreduce routine
 *
 * This functions wraps the MPI_Allreduce routine, reducing values from 
 * all ranks and broadcasting the result to all ranks.
 *
 * @param send_buffer Pointer to input buffer.
 * @param recv_buffer Pointer to output buffer.
 * @param count       Number of elements to reduce. 
 * @param datatype    MPI_Datatype of elements.
 * @param operation   MPI_Op reduction operation.
 * @param comm        MPI communicator over which to perform the reduction.
 *
 */
void reduce_and_broadcast(const void *send_buffer, void *recv_buffer, int count,
                  MPI_Datatype datatype, MPI_Op operation, MPI_Comm comm) {
    
    MPI_Allreduce(send_buffer, recv_buffer, count, datatype, operation, comm);
}

/**
 * @brief Performs MPI_Exscan routine
 *
 * This function wraps the MPI_Exscan routine, performing an 
 * exclusive prefix reduction
 *
 * @param send_buffer Pointer to input buffer.
 * @param recv_buffer Pointer to output buffer.
 * @param count       Number of elements to reduce.
 * @param datatype    MPI_Datatype of elements.
 * @param operation   MPI_Op reduction operation.
 * @param comm        MPI communicator over which to perform the collective.
 **/
void exclusive_scan(const void *send_buffer, void *recv_buffer, int count,
                  MPI_Datatype datatype, MPI_Op operation, MPI_Comm comm) {
    
    MPI_Exscan(send_buffer, recv_buffer, count, datatype, operation, comm);
}

/**
 * @brief Performs MPI_Barrier routine
 *
 * This funtion wraps the MPI barrier, synchronizing all 
 * ranks in MPI_COMM_WORLD.
 */
void waitForProcesses(void) {
    MPI_Barrier(MPI_COMM_WORLD);
}

/**
 * @brief Performs MPI_Abort routine
 *
 * This function abort all ranks in MPI_COMM_WORLD with error code -1.
 */
void exitParallelContext(void) {
    MPI_Abort(MPI_COMM_WORLD, -1);
}

/**
 * @brief Performs MPI_Finalize routine.
 *
 * This function wraps the MPI_Finalize routine, finalizing the 
 * MPI environment.
 *
 */
void endParallelContext(void) {
    MPI_Finalize();
}

/**
 * @brief Performs MPI_Wtime routine.
 *
 * This function wraps the MPI_Wtime routine, returning the current
 * wall-clock time in seconds
 *
 * @return current wall-clock time in seconds
 */
double getTime(void) {
    return MPI_Wtime();
}


/**
 * @brief 1D decomposition of a global size across ranks.
 *
 * Splits a global size across all MPI processes.
 * Each calling process calculates a local size equal to the 
 * global size divided by the number of processes. If the global size
 * is not divisible by the number of processes, the remainder is 
 * split evenly across processes with ranks < remainder. 
 *
 * This function was taken and adapted from: 
 * https://gitlab.spack.io/adios2/adios2/-/blob/v2.10.0/examples/basics/globalArray1D/decomp.c?ref_type=tags
 *
 * @param global_size  Total number of items.
 * @param offset       Reference to the starting global index for the calling process.
 * @param local_size   Reference to the number of items assigned to the calling process. 
 * @param nproc        Total number of MPI processes.
 * @param rank         Rank of the calling process. 
 */
void decompose1D(size_t global_size, size_t &offset, size_t &local_size, int nproc, int rank) {
    int remainder;
    local_size = global_size / nproc;
    remainder = global_size - (nproc * local_size);

    if (rank < remainder) {
        local_size = local_size + 1;
        offset = rank * local_size;
    } else {
        offset = rank * local_size + remainder;
    }
}