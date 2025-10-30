/**
 * @file serialPipeline.cpp
 * @brief This script is a serial pipeline with encryption,
 * write, read, and decryption stages. 
 * @author Iole Bolognesi
 * 
 * This script executes a pipeline that encrypts a dataset using 
 * Crypto++, writes the corresponding cipher-text, reads in back, 
 * and decrypts it using Crypto++.
 */

#include <files.h>
#include <filesystem>
#include <default.h> 
#include <osrng.h>
#include <hrtimer.h>
#include <string>
#include <string_view>

#include "fileIO.hpp"
#include "parsing.hpp"
#include "libpar.hpp"
#include "cryptography.hpp"
#include "CipherFactory.hpp"
#include "Cipher.hpp"

using namespace CryptoPP;

/* minimum runtime seconds for valid measurements */
const double min_runtime_seconds = 1.0; 

/* CPU frequency */
const double cpu_frequency = 2.1 * 1000 * 1000 * 1000; 

int main(int argc, char *argv[]) {
 
    try
    {  
        int rank=0;    
        int nproc=1;  
        
        if(argc != 3){
            std::cout << "Usage : ./bin/serial <dataset directory> "
                        "<ALGORITHM_MODE>" << std::endl;
            exit(1);
        }

        /* Initialize MPI so to use the MPI timer */ 
        adios2::ADIOS adios = initParallelContext(argc, argv, rank, nproc);

        /* Configure input and output directories */

        std::string dataset_directory = argv[1]; 
        const std::filesystem::path output_path{"output"};
        setDirectory(output_path);
        const std::filesystem::path data_path{dataset_directory};
        const std::filesystem::path encryption_output_path{"output/encryptedData/ciphertext"};
        const std::filesystem::path decryption_output_path{"output/decryptedData/"};
        const std::filesystem::path metadata_output_path{"output/metadata/metadatafile"};

        /* Configure cipher type and mode */

        std::string cipher_name = argv[2]; 
        CipherType cipher_type {getEnumFromString(std::string_view{cipher_name}, 0)};
        
        CipherFactory f;
        std::unique_ptr<Cipher> cipher = f.createCipher(cipher_type);  
        auto encryptor = cipher->createEncryptor();

        std::visit([&](auto &pointer){     

            /* Deference pointer to get CryptoPP encryption object */
            auto &encryption_object = *pointer;      

            std::cout << encryption_object.AlgorithmName() << 
                        " Encryption Benchmark" << std::endl;
        }, encryptor);

        /* Serial Encryption */

        std::vector<unsigned char> ciphertext;
        std::vector <CTMeta> ciphertexts_info; 
        size_t file_offset=0;
        std::cout<< "Encrypting... " << std::endl;

        double encryption_start, encryption_end, encryption_seconds;

        encryption_start = getTime();
        
        for (auto const &file_directory: 
            std::filesystem::directory_iterator{data_path}){

            std::vector<unsigned char> plaintext = loadFile(file_directory.path());
            std::vector<unsigned char> padded_plaintext(plaintext);
    
            /* Add padding */
            if(cipher->requiresPadding()){
                addPadding(padded_plaintext, N_BLOCK_BYTES);
            }

            size_t input_size = padded_plaintext.size();
            std::vector<unsigned char> file_ciphertext(input_size);
            
            std::visit([&](auto &pointer){

                /* Deference pointer to get Crypto++ encryption object */
                auto &encryption_object = *pointer;           

                /* Encrypt */
                encryption_object.ProcessData(file_ciphertext.data(),
                                            padded_plaintext.data(),
                                            input_size);
            }, encryptor);

            ciphertext.insert(ciphertext.end(), file_ciphertext.begin(), 
                            file_ciphertext.end()); 

            /* Save metadata of file being encrypted in vectors */
            ciphertexts_info.push_back({file_directory.path().filename(), 
                                        input_size, file_offset}); 
            file_offset += input_size ; 
        }

        encryption_end = getTime();
        encryption_seconds = encryption_end - encryption_start;
        
        std::cout << "Encryption time (s) = " << encryption_seconds <<std::endl;

        /* Serial write of data */

        int write_data_iterations=0;
        int write_metadata_iterations=0;
        double write_data_start, write_data_end, write_data_seconds;
        double write_metadata_start, write_metadata_end, write_metadata_seconds ;

        write_data_start = getTime();
        
        do{
            saveFile(encryption_output_path, ciphertext); 
            write_data_end = getTime();
            write_data_iterations++;
            write_data_seconds = write_data_end - write_data_start;
        }
        while (write_data_seconds < min_runtime_seconds);

        /* Serial write of metadata */
        write_metadata_start = getTime();
        do{
            saveMetadataFile(metadata_output_path, ciphertexts_info);
            write_metadata_end=getTime();
            write_metadata_iterations++;
            write_metadata_seconds = write_metadata_end - write_metadata_start;
        }
        while (write_metadata_seconds < min_runtime_seconds);
        
        std::cout << "Serial write data time (s) = " << write_data_seconds <<
                    " for " << write_data_iterations << " iterations"<< std::endl;
        
        std::cout << "Serial write metadata time (s) = " << write_metadata_seconds <<
                     " for " << write_metadata_iterations << " iterations"<< std::endl;
  
        /* Serial read of data */

        int read_data_iterations=0;
        int read_metadata_iterations=0;
        std::vector<unsigned char> ciphertext_read;
        std::vector<CTMeta> metadata_read;

        double read_data_start,read_data_end, read_data_seconds;
        double read_metadata_start, read_metadata_end, read_metadata_seconds;

        read_data_start=getTime();

        do{
            ciphertext_read = loadFile(encryption_output_path);  
            read_data_end=getTime();
            read_data_iterations++;
            read_data_seconds = read_data_end - read_data_start; 
        }
       while (read_data_seconds < min_runtime_seconds);

        /* Serial read of metadata */
        read_metadata_start=getTime();

        do{
            metadata_read = loadMetadataFile(metadata_output_path); 
            read_metadata_end=getTime();
            read_metadata_iterations++;
            read_metadata_seconds = read_metadata_end - read_metadata_start; 
       }
        while (read_metadata_seconds < min_runtime_seconds);
        
        std::cout << "Serial read data time (s) = " << read_data_seconds <<
                    " for " << read_data_iterations << " iterations"<< std::endl;
        
        std::cout << "Serial read metadata time (s) = " << read_metadata_seconds <<
                    " for " << read_metadata_iterations << " iterations"<< std::endl; 
                
        /* Serial Decryption */

        auto decryptor = cipher->createDecryptor();
        std::cout<< "Decrypting..."<< std::endl;

        for (const auto &CT_meta_data : metadata_read) {
        
            std::vector<unsigned char> padded_plaintext(CT_meta_data.size);

            std::visit([&](auto &pointer) {

                /* Deference pointer to access Crypto++ encryption object */
                auto &decryption_object = *pointer;

                /* Decryption */
                decryption_object.ProcessData(
                    padded_plaintext.data(),
                    ciphertext_read.data() + CT_meta_data.offset,
                    CT_meta_data.size);
            }, decryptor);

            std::vector<unsigned char> plaintext(padded_plaintext);

            /* Remove padding */
            if(cipher->requiresPadding()){
                removePadding(plaintext);
            }

            const std::string decrypted_file_name = decryption_output_path.string() + 
                                                    CT_meta_data.file_name;

            saveFile(decrypted_file_name, plaintext);  
        }

        std::cout << "The program finished decryption" <<std::endl;
        
        return 0;
    }

    catch (std::exception  &e){
        
        std::cout<< e.what() << std::endl;

        exit(1);
    }

}

