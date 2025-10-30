/**
 * @file FileIO.hpp
 * @brief This module declares functions for serial buffered I/O 
 * @author Iole Bolognesi
 *
 * This module declares the CTMeta struct and functions to write and read binary
 * files as well as metadata files, and configure working directories.
 */
#ifndef HEADER_FILEIO
#define HEADER_FILEIO

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

/* Structure of metadata for the cipher-text in the serial pipeline */
struct CTMeta {
    std::string file_name;
    size_t size;
    size_t offset;
    friend std::istream& operator>>(std::istream& input, CTMeta& metadata);
};
std::vector<CTMeta> loadMetadataFile(const std::filesystem::path file_name);
std::vector<unsigned char> loadFile(const std::filesystem::path file_name);
void saveMetadataFile(const std::filesystem::path file_name, const std::vector<CTMeta> &metadata);
void saveFile(const std::filesystem::path file_name, const std::vector<unsigned char> &data);
void setDirectory(const std::filesystem::path directory_name);
#endif