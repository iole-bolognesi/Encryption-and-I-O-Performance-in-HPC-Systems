/** 
* @file adios_io.cpp
* @brief This module defines ADIOS 2 functions for parallel I/O 
* @author Iole Bolognesi 
* 
* This module provides utility functions for reading and writing 
* to a file in parallel using the ADIOS 2 framework. 
*
*/

#include "adios.hpp"
#include "libpar.hpp"

/**
 * @brief Writes encryption metadata in parallel using ADIOS 2.
 *
 * This function writes encryption metadata in parallel to an ADIOS 2 file. 
 * The function stores 4 global ADIOS 2 variables: "local_sizes", "global_offsets", 
 * "files_sizes", and "files_offsets".
 *
 * @param adios                 Reference to the ADIOS2 context object.
 * @param nproc                 Total number of MPI processes writing metadata.
 * @param rank                  MPI rank of the calling process.
 * @param count                 Number of entries the calling process will write for 
 *                              the local_sizes and global_offsets ADIOS 2 variables.
 * @param CT_local_size         Size of the local cipher-text.
 * @param CT_global_offset      Offset of where the local cipher-text fits within the 
 *                              global cipher-text.
 * @param CTmeta_global_size    Total number of metadata entries across all processes.
 * @param CTmeta_local_size     Number of local metadata entries.
 * @param CTmeta_global_offset  Offset of where the local metadata fits within the global 
 *                              metadata. 
 * @param files_sizes           Vector containing sizes of each file cipher-text
                                contained in the local cipher-text.
 * @param files_offsets         Vector containing offsets of each file cipher-text
                                contained in the local cipher-text. 
 * @param file_name             Name of the ADIOS2 output file.
 * @param iter_id               Iteration id for repeated write operations
 */
void parallelWriteMetadata(adios2::ADIOS &adios, size_t nproc, size_t rank,
                        size_t count, size_t CT_local_size, size_t CT_global_offset,
                        size_t CTmeta_global_size, 
                        size_t CTmeta_local_size, size_t CTmeta_global_offset, 
                        std::vector<size_t> &files_sizes,
                        std::vector<size_t> &files_offsets,
                        const std::string file_name, std::string iter_id){
        
        std::string writer_name = "MetadataWriter" + iter_id;
   
        adios2::IO io = adios.DeclareIO(writer_name);


        auto var_CT_sizes = io.DefineVariable<size_t>("local_sizes",
                                            {nproc}, {rank}, {count});
       
        auto var_CT_offsets = io.DefineVariable<size_t>("global_offsets",
                                            {nproc}, {rank}, {count});
       
        auto var_files_sizes = io.DefineVariable<size_t>("files_sizes",
                            {CTmeta_global_size}, {CTmeta_global_offset}, {CTmeta_local_size});
               
        auto var_files_offsets = io.DefineVariable<size_t>("files_offsets",
                            {CTmeta_global_size}, {CTmeta_global_offset}, {CTmeta_local_size});


        adios2::Engine writer = io.Open(file_name, adios2::Mode::Write);
        writer.BeginStep();
        writer.Put(var_CT_sizes, &CT_local_size);
        writer.Put(var_CT_offsets, &CT_global_offset);
        writer.Put(var_files_sizes, files_sizes.data());
        writer.Put(var_files_offsets, files_offsets.data());
        writer.EndStep();
        writer.Close();
}

/**
 * @brief Reads encryption metadata in parallel using ADIOS 2.
 *
 * This function reads encryption metadata in parallel from an ADIOS 2 file. 
 * The function retrieves 4 global ADIOS 2 variables: "local_sizes", "global_offsets", 
 * "files_sizes", and "files_offsets".
 *
 * @param adios                 Reference to the ADIOS2 context object.
 * @param file_name             Name of the ADIOS2 file to be read.
 * @param nproc                 Total number of MPI processes reading metadata.
 * @param rank                  MPI rank of the calling process.
 * @param count                 Number of entries the calling process will read for 
 *                              the local_sizes and global_offsets ADIOS 2 variables.
 * @param CTmeta_global_offset  Offset of where the local metadata fits within the global 
 *                              metadata. 
 * @param CTmeta_local_size     Number of local metadata entries.
 * @param iter_id               Iteration id for repeated read operations
 */
ParallelCTMeta parallelReadMetadata(adios2::ADIOS &adios, const std::string file_name,
                                size_t nproc, size_t rank, size_t count,
                                size_t CTmeta_global_offset, size_t CTmeta_local_size,
                                std::string iter_id){
       
        ParallelCTMeta metadata;
        metadata.files_sizes.resize(CTmeta_local_size);
        metadata.files_offsets.resize(CTmeta_local_size);

        std::string reader_name = "MetadataReader" + iter_id;
   
        adios2::IO io = adios.DeclareIO(reader_name);
        adios2::Engine reader = io.Open(file_name, adios2::Mode::Read);

        reader.BeginStep();

        auto var_CT_size = io.InquireVariable<size_t>("local_sizes");
        var_CT_size.SetSelection({{rank}, {count}});
        reader.Get(var_CT_size, &metadata.local_size);

        auto var_CT_offset = io.InquireVariable<size_t>("global_offsets");
        var_CT_offset.SetSelection({{rank}, {count}});
        reader.Get(var_CT_offset, &metadata.global_offset);

        auto var_files_sizes = io.InquireVariable<size_t>("files_sizes");
        var_files_sizes.SetSelection({{CTmeta_global_offset}, {CTmeta_local_size}});
        reader.Get(var_files_sizes, metadata.files_sizes.data());
        
        auto var_files_offsets = io.InquireVariable<size_t>("files_offsets");
        var_files_offsets.SetSelection({{CTmeta_global_offset}, {CTmeta_local_size}});
        reader.Get(var_files_offsets, metadata.files_offsets.data());
                                
        reader.EndStep();

        reader.Close();

        return metadata;
}

 /**
 * @brief Writes a cipher-text (binary data) to a file in parallel using ADIOS2.
 *
 * This function writes a vector of bytes in parallel to an ADIOS 2 file. 
 *
 * @param adios                 Reference to the ADIOS2 context object.
 * @param file_name             Name of the ADIOS2 output file.
 * @param data                  Vector containing binary data.
 * @param shape                 Size of the global cipher-text across all processes. 
 * @param count                 Size of the local cipher-text.
 * @param start                 Offset of the local cipher-text within the global 
 *                              cipher-text. 
 * @param iter_id               Iteration id for repeated write operations
 */
void parallelWriteData(adios2::ADIOS &adios, std::vector<uint8_t> &data, 
                  const std::string file_name, size_t shape, size_t count, 
                  size_t start, std::string iter_id){

        std::string writer_name = "DataWriter" + iter_id;
   
        adios2::IO io = adios.DeclareIO(writer_name);

        auto var = io.DefineVariable<uint8_t>("binary_data", {shape}, {start}, {count});

        adios2::Engine writer = io.Open(file_name, adios2::Mode::Write);
        writer.BeginStep();
        writer.Put(var, data.data());
        writer.EndStep();
        writer.Close();

}


 /**
 * @brief Reads a cipher-text (binary data) from a file in parallel using ADIOS2.
 *
 * This function reads a vector of bytes in parallel from an ADIOS 2 file. 
 *
 * @param adios                 Reference to the ADIOS2 context object.
 * @param file_name             Name of the ADIOS2 file to be read.
 * @param count                 Size of the local cipher-text.
 * @param start                 Offset of the local cipher-text within the global 
 *                              cipher-text. 
 * @param iter_id               Iteration id for repeated read operations
 */
std::vector<uint8_t> parallelReadData(adios2::ADIOS &adios, const std::string file_name, 
                                size_t count, size_t start, std::string iter_id) {

        std::string reader_name = "DataReader" + iter_id;
   
        adios2::IO io = adios.DeclareIO(reader_name);
        adios2::Engine reader = io.Open(file_name, adios2::Mode::Read);

        reader.BeginStep();

        auto var = io.InquireVariable<uint8_t>("binary_data");
    
        var.SetSelection({{start}, {count}});
        
        std::vector<uint8_t> buffer(count);

        if (!var)
        {
            throw std::runtime_error ("Variable not found by adios2 reader");
        }

        reader.Get(var, buffer);

        reader.EndStep();
        
        reader.Close();

        return buffer;
}