/**
 * @file parallelPipeline.cpp
 * @brief This script is a parallel pipeline with encryption,
 * write, read, and decryption stages. 
 * @author Iole Bolognesi
 * 
 * This script executes a pipeline that encrypts a dataset in parallel 
 * using Crypto++ and through distributed memory parallelism, writes the corresponding 
 * cipher-text in parallel through ADIOS 2, reads in back in parallel 
 * through ADIOS 2, and decrypts it in parallel using Crypto++ and 
 * through distributed memory parallelism. 
 */

#include <files.h>
#include <filesystem>
#include <fstream>
#include <default.h> 
#include <osrng.h>
#include <string>
#include <string_view>
#include <cstdlib>

#include "libpar.hpp"
#include "adios.hpp"
#include "fileIO.hpp"
#include "parsing.hpp"
#include "cryptography.hpp"
#include "CipherFactory.hpp"
#include "Cipher.hpp"

using namespace CryptoPP;

/* minimum runtime seconds for valid measurements */
const double min_runtime_seconds = 3.0; 

/* CPU frequency */
const double cpu_frequency = 2.1 * 1000 * 1000 * 1000; 

int main(int argc, char *argv[]) {
 
    try
    {      
        int rank=0;
        int nproc=1;

        /* Initialize MPI and ADIOS2 */
        adios2::ADIOS adios = initParallelContext(argc, argv, rank, nproc);

        if (!adios) {
            std::runtime_error("Failed to initialize ADIOS\n");
            exitParallelContext();
            exit(1);
        }


        if(argc != 3){
            if(rank==0){
                std::cout << "Usage : mpirun -n <number> ./bin/parallel <dataset directory> "
                        "<ALGORITHM_MODE>" << std::endl;
            }
            exit(1);
        }

        /* Configure input and output directories */

        std::string dataset_directory = argv[1]; 
        const std::filesystem::path data_path{dataset_directory};
        const std::filesystem::path output_path{"output"};
        
        if(rank==0){
            setDirectory(output_path);
        }
        waitForProcesses();

        const std::filesystem::path encryption_output_path = "output/encryptedData";
        const std::filesystem::path decryption_output_path = "output/decryptedData/";
        const std::filesystem::path metadata_output_path = "output/metadata";

        /* Configure cipher type and mode */

        std::string cipher_name = argv[2]; 
        CipherType cipher_type {getEnumFromString(std::string_view{cipher_name}, rank)};
        
        CipherFactory f;
        std::unique_ptr<Cipher> cipher = f.createCipher(cipher_type);  
        auto encryptor = cipher->createEncryptor();

        if(rank==0){
            std::visit([&](auto &pointer){          

                /* deference pointer to get Crypto++ encryption object */
                auto &encryption_object = *pointer;         

                std::cout << encryption_object.AlgorithmName() << 
                            " Encryption Benchmark" << std::endl;
            }, encryptor);
        }

        /* Dataset Partitioning */

        std::vector <std::filesystem::path> files_list;
        std::vector<size_t> counts(nproc);
        std::vector<size_t> displacements(nproc);

        for (auto const &entry_directory: 
            std::filesystem::directory_iterator{data_path}){
            files_list.push_back(entry_directory.path());
        }

        /* Calculation of how many dataset files each process encrypts 
        and starting from which offset in the data directory */

        for(int i=0; i<nproc; i++){
            decompose1D(files_list.size(), displacements[i], counts[i], nproc, i);
        }

        size_t local_start_idx= displacements[rank];
        size_t local_end_idx= displacements[rank] + counts[rank];

        /* Parallel Encryption */

        std::vector<unsigned char> ciphertext;
        std::vector<size_t> files_sizes;
        std::vector<size_t> files_offsets;
        size_t file_offset=0;
        
        if (rank==0){
            std::cout<< "Encrypting... " << std::endl;
        }
        
        double encryption_seconds, start_encryption_time, end_encryption_time; 
        waitForProcesses();
        start_encryption_time = getTime();
            
        for (size_t i=local_start_idx; i<local_end_idx; i++){

            std::vector<unsigned char> plaintext = loadFile(files_list[i]);
            std::vector<unsigned char> padded_plaintext(plaintext);
    
            /* Add padding */
            if(cipher->requiresPadding()){
                addPadding(padded_plaintext, N_BLOCK_BYTES);
            }

            size_t input_size = padded_plaintext.size();
            std::vector<unsigned char> file_ciphertext(input_size); 

            std::visit([&](auto &pointer){
                
                /* Deference pointer to access Crypto++ encryption object */
                auto &encryption_object = *pointer;           

                /* Encryption */
                encryption_object.ProcessData(file_ciphertext.data(), 
                                            padded_plaintext.data(), 
                                            input_size);

            }, encryptor);

            ciphertext.insert(ciphertext.end(), file_ciphertext.begin(), 
                                file_ciphertext.end());

            /* Save metadata of file being encrypted in vectors */
            files_sizes.push_back(input_size);
            files_offsets.push_back(file_offset);
            
            file_offset += input_size; 
        }

        waitForProcesses();
        end_encryption_time = getTime();
        encryption_seconds = end_encryption_time - start_encryption_time;   
        
        if (rank==0){
            std::cout << " Parallel encryption time (s) = " << 
                        encryption_seconds <<std::endl;
        }
 
        /* Parallel Write of metadata */
        size_t CT_local_size=ciphertext.size();
        size_t CT_global_size;
        size_t CT_global_offset;

        int write_data_iterations=0;
        int write_metadata_iterations=0;
        double write_data_seconds, start_write_data, end_write_data; 
        double write_metadata_seconds, start_write_metadata, end_write_metadata; 
        
        waitForProcesses();  
        start_write_metadata = getTime();

        do{
            /* Calculate size of global cipher-text */
            reduce_and_broadcast(&CT_local_size, &CT_global_size, 1, MPI_UINT64_T, MPI_SUM, 
                                MPI_COMM_WORLD);

            /*Calculate global offset of local cipher-texts 
            within the global cipher-text. */
            exclusive_scan(&CT_local_size, &CT_global_offset, 1, MPI_UINT64_T, MPI_SUM, 
                    MPI_COMM_WORLD);

            if(rank==0){
                CT_global_offset=0;
            };

            parallelWriteMetadata(adios, nproc, rank, 1, CT_local_size, CT_global_offset, 
                                    files_list.size(), counts[rank], displacements[rank], 
                                    files_sizes, files_offsets, metadata_output_path,
                                    std::to_string(write_metadata_iterations));

            waitForProcesses();
            end_write_metadata = getTime();

            write_metadata_iterations++;

            write_metadata_seconds = end_write_metadata - start_write_metadata;
        }
        while (write_metadata_seconds < min_runtime_seconds);


        /* Parallel write of cipher-text */
        waitForProcesses();
        start_write_data = getTime();

        do{
            parallelWriteData(adios, ciphertext, encryption_output_path, CT_global_size , 
                    CT_local_size, CT_global_offset, std::to_string(write_data_iterations));
            
            waitForProcesses();
            end_write_data = getTime();

            write_data_iterations++;

            write_data_seconds = end_write_data - start_write_data;
        }
        while(write_data_seconds < min_runtime_seconds);

        if (rank==0){
            std::cout<< "Parallel data writing time (s) = " << write_data_seconds << 
                         " for " << write_data_iterations << " iterations"<< std::endl;

            std::cout<< "Parallel metadata writing time (s) = " << write_metadata_seconds << 
                        " for " << write_metadata_iterations << " iterations"<< std::endl;
        }

        /* Parallel read of metadata */
        std::vector<unsigned char> ciphertext_read(CT_local_size);
        ParallelCTMeta metadata_read;
        int read_data_iterations=0;
        int read_metadata_iterations=0;
        double read_data_seconds, start_read_data, end_read_data; 
        double read_metadata_seconds, start_read_metadata, end_read_metadata; 
        
        waitForProcesses();  
        start_read_metadata = getTime();

        do{
            metadata_read = parallelReadMetadata(adios, metadata_output_path, nproc, rank, 1,
                                             displacements[rank], counts[rank],
                                             std::to_string(read_metadata_iterations));
            waitForProcesses();
            end_read_metadata = getTime();

            read_metadata_iterations++;

            read_metadata_seconds = end_read_metadata - start_read_metadata;
        }
        while (read_metadata_seconds < min_runtime_seconds);
        
        /* Parallel read of cipher-text */
        waitForProcesses();
        start_read_data = getTime();

        do{
            ciphertext_read = parallelReadData(adios, encryption_output_path, 
                                            metadata_read.local_size, 
                                            metadata_read.global_offset,
                                            std::to_string(read_data_iterations));
            waitForProcesses();
            end_read_data = getTime();

            read_data_iterations++;

            read_data_seconds = end_read_data - start_read_data;
        }
        while (read_data_seconds < min_runtime_seconds);
        

        if (rank==0){
            std::cout<< "Parallel data reading time (s) = " << read_data_seconds << 
                         " for " << read_data_iterations << " iterations"<< std::endl;

            std::cout<< "Parallel metadata reading time (s) = " << read_metadata_seconds << 
                        " for " << read_metadata_iterations << " iterations"<< std::endl;
        }

        /* Parallel Decryption */

        auto decryptor = cipher->createDecryptor();
        
        if (rank==0){
            std::cout<< "Decrypting... " << std::endl;
        }

        for (size_t i=local_start_idx; i<local_end_idx; i++){

            size_t local_index= i-local_start_idx;
        
            std::vector<unsigned char> padded_plaintext(metadata_read.files_sizes[local_index]);
            
            std::visit([&](auto &pointer) {

                /* Deference pointer to access Crypto++ encryption object */
                auto &decryption_object = *pointer;

                /* Decryption */
                decryption_object.ProcessData(
                padded_plaintext.data(),
                ciphertext_read.data() + metadata_read.files_offsets[local_index],
                metadata_read.files_sizes[local_index]);

            }, decryptor);

            std::vector<unsigned char> plaintext(padded_plaintext);

            /* Remove padding */
            if(cipher->requiresPadding()){
                removePadding(plaintext);
            }

            const std::string decrypted_file_name = decryption_output_path.string() + 
                                                    files_list[i].filename().string();

            saveFile(decrypted_file_name, plaintext); 
        }

        if (rank==0){
            std::cout << "The program finished decryption" <<std::endl;
        }
        
        endParallelContext();

        return 0;
    }

    catch (std::exception  &e){
        
        std::cout<< e.what() << std::endl;

        exitParallelContext();

        exit(1);
    }

}

