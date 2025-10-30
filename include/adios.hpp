/**
 * @file adios_io.hpp
 * @brief This module declares ADIOS2 utilities for parallel data and metadata 
 * I/O operations 
 * @author Iole Bolognesi
 *
 * This module declares functions to read and write metadata as well as cipher data
 (raw byte buffers) through ADIOS2. 
 */
#ifndef INCLUDE_ADIOS_HEADER
#define INCLUDE_ADIOS_HEADER

#include <adios2.h>
#include <string>
#include "libpar.hpp"

void parallelWriteMetadata(adios2::ADIOS &adios, size_t nproc, size_t rank,
                        size_t count, size_t CT_local_size, 
                        size_t CT_global_offset,
                        size_t CTmeta_global_size, 
                        size_t CTmeta_local_size, size_t CTmeta_global_offset, 
                        std::vector<size_t> &files_sizes,
                        std::vector<size_t> &files_offsets,
                        const std::string file_name, std::string iter_id);

ParallelCTMeta parallelReadMetadata(adios2::ADIOS &adios, const std::string file_name,
                                size_t nproc, size_t rank, size_t count,
                                size_t CTmeta_global_offset, 
                                size_t CTmeta_local_size, std::string iter_id);

void parallelWriteData(adios2::ADIOS &adios, std::vector<uint8_t> &data, 
                  const std::string file_name, size_t shape, size_t count, 
                  size_t start, std::string iter_id);

std::vector<uint8_t> parallelReadData(adios2::ADIOS &adios, const std::string file_name,
                                    size_t count, size_t start, std::string iter_id);
#endif 