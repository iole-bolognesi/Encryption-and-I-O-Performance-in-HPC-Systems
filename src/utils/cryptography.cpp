/** 
* @file cryptography.cpp
* @brief This module defines functions to apply and remove PKCS#7 padding.
* @author Iole Bolognesi 
* 
* This module provides utility functions for applying and removing a
* PKCS#7 padding. to a vector of bytes. 
*
*/

#include "cryptography.hpp"

 /**
 * @brief Applies PKCS#7 padding to a vector of bytes.
 *
 * This function appends PKCS#7-style padding bytes to the input vector 
 * so that its size becomes a multiple of the specified block size.
 * The value of each padding byte is equal to the total number of padding bytes added
 * according to PKCS#7 style. 
 *
 * @param input       Reference to the vector of bytes to be padded.
 * @param block_size  Block size in bytes.
 */
void addPadding(std::vector<unsigned char> &input, int block_size){
    
    int padding_size = block_size - (input.size() % block_size);
    
    input.insert(input.end(), padding_size, static_cast<unsigned char>(padding_size));
}


/**
 * @brief Removes PKCS#7 padding from a vector of bytes.
 *
 * This function removes as many bytes from a vector as the value of
 * the last byte, according to PKCS#7 style.
 *
 * @param input  Reference to the vector of bytes from which padding will be removed.
 */
void removePadding(std::vector<unsigned char> &input) {
    
    unsigned char padding_value = input.back(); 

    input.resize(input.size() - padding_value);
}