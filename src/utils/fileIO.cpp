/** 
* @file fileIO.cpp
* @brief This module defines serial I/O functions to read 
* and write files with different structures.
* @author Iole Bolognesi 
* 
* This module provides utility functions for reading and writing a
* binary file serially through buffered I/O operations as well as 
* functions to read and write a file containing CTMeta objects.
*/

#include "fileIO.hpp"


/**
 * @brief Stream extraction operator for CTMeta objects.
 *
 * Reads the file name, size, and offset values from a given input stream
 * and assigns them to the corresponding members of a CTMeta object.
 *
 * @param input      Reference to the stream to read from.
 * @param metadata   Reference to a CTMeta object to be configured.
 * @return Reference to the input stream.
 */
std::istream& operator>>(std::istream& input, CTMeta& metadata){
    input >> metadata.file_name;
    input >> metadata.size;
    input >> metadata.offset;
    return input;
}


 /**
 * @brief Loads the contents of a binary file into a buffer.
 *
 * This function opens a given file in binary mode and reads all bytes into a 
 * vector of bytes. 
 *
 * This implementation was taken and adapted from:
 * https://medium.com/@jmayuresh25/create-a-simple-file-encryption-system-in-c-e3726e0f265b
 *
 * @param file_name  Path to the file to load.
 * @return A vector of bytes corresponding to the file's content.
 *
 * @throws std::runtime_error if the file cannot be opened.
 *
 * @note Requires C++17 or later for std::filesystem.
 */
std::vector<unsigned char> loadFile(const std::filesystem::path file_name){

    std::filesystem::path file_path{file_name};
    auto length = std::filesystem::file_size(file_path);
    
    if (length == 0) {
        std::cout<<"File is empty, nothing to decrypt" <<std::endl;
        exit(1);
    }

    std::vector<unsigned char> buffer(length);
    std::ifstream file_stream(file_name, std::ios_base::binary);

    if (!file_stream) {
        throw std::runtime_error("Failed to open file for reading: " + file_name.string());
    }

    file_stream.read(reinterpret_cast<char*>(buffer.data()), length);
    file_stream.close();
    
    return buffer;
}

/**
 * @brief Loads the contents of a file into a vector of CTMeta objects.
 *
 * This function opens a given file and reads all bytes into a 
 * vector of CTMeta objects. It assumes the file read uses the format: 
 *       <file_name> <size> <offset>
 *
 * @param file_name  Path to the metadata file.
 * @return A vector of CTMeta objects loaded from the file.
 *
 * @throws std::runtime_error If the file cannot be opened.
 *
 */
std::vector<CTMeta> loadMetadataFile(const std::filesystem::path file_name){

    std::filesystem::path file_path{file_name};
    std::vector<CTMeta> metadata;
    CTMeta metadata_object;
    auto length = std::filesystem::file_size(file_path);
    
    if (length == 0) {
        std::cout<<"File is empty, no metadata to read" <<std::endl;
        exit(1);
    }

    std::ifstream file_stream(file_name);

    if (!file_stream) {
        throw std::runtime_error("Failed to open file for reading: " + file_name.string());
    }
    
    while (file_stream >> metadata_object){
        metadata.push_back(metadata_object);
    }
    
    file_stream.close();
    
    return metadata;
}


/**
 * @brief Writes a vector of bytes to a file.
 *
 * This function writes a given vector of bytes to a file, in binary mode.
 *
 * @param file_name  Path to the file to write.
 * @param data       Vector containing the data to write.
 *
 * @throws std::runtime_error If the file cannot be opened for writing.
 */
void saveFile(const std::filesystem::path file_name, const std::vector<unsigned char> &data) {
    std::ofstream file(file_name, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Failed to open file for writing: " + file_name.string());
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
}

/**
 * @brief Writes a vector of CTMeta objects to a file.
 *
 * This function writes a given vector of CTMeta objects 
 * in the format: <file_name> <size> <offset>.
 *
 * @param file_name  Path to the file to write.
 * @param data       Vector containing the data to write.
 *
 * @throws std::runtime_error If the file cannot be opened for writing.
 */
void saveMetadataFile(const std::filesystem::path file_name, const std::vector<CTMeta> &metadata) {
    
    std::ofstream file(file_name);
    
    if (!file) throw std::runtime_error("Failed to open file for writing: " + file_name.string());

    for (const auto& meta : metadata) {
        file << meta.file_name << " " << meta.size << " " << meta.offset << "\n";
    }
    file.close();
}

/**
 * @brief Creates or resets a directory structure for encryption output.
 *
 * If the specified directory exists, all its contents are removed. 
 * If it does not exist, it is created. In either case, it then creates 
 * three subdirectories: "encryptedData", "decryptedData", and "metadata". 
 *
 * @param directory_name  Path to the directory to be configured.
 *
 */
void setDirectory(const std::filesystem::path directory_name){
    
    if (std::filesystem::exists(directory_name)) {
        /*Remove contents of the directory iteratively */
        for (auto &entry : std::filesystem::directory_iterator(directory_name)) {
            std::filesystem::remove_all(entry);
        }
    } 
    else {
        std::filesystem::create_directories(directory_name);
    }

    std::filesystem::create_directories(directory_name / "encryptedData");
    std::filesystem::create_directories(directory_name / "decryptedData");
    std::filesystem::create_directories(directory_name / "metadata");

}