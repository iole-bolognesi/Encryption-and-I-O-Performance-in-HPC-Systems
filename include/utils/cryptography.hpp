/**
 * @file Cryptography.hpp
 * @brief This module declares PKCS#7 padding utility functions for byte buffers
 * @author Iole Bolognesi
 *
 * This module declares functions to add and remove PKCS#7-style 
 * padding on a vector of bytes.
 */
#ifndef HEADER_CRYPTOGRAPHY
#define HEADER_CRYPTOGRAPHY

#include <vector>

void addPadding(std::vector<unsigned char> &input, int block_size);

void removePadding(std::vector<unsigned char> &input);

#endif 