/** 
* @file Cipher.cpp
* @brief This module provides the constructor of the Cipher class. 
* @author Iole Bolognesi 
* 
* This module uses the Crypto++ library for constructing objects
* of the Cipher class (declared in Cipher.hpp)
*
*/
#include "Cipher.hpp"
#include <iostream>

using namespace CryptoPP;
/**
 * @brief Constructs a Cipher object with a cryptographic key and IV.
 *
 * This function uses the Crypto++ library to constructs a Cipher object 
 * and initialize the class members key and an IV with randomly generated 
 * sequences of bytes. 
 *
 * @param n_key_bytes  Desired key length in bytes. 
 **/
Cipher::Cipher(int n_key_bytes){

    SecByteBlock key(n_key_bytes);
    SecByteBlock iv(N_BLOCK_BYTES); 

    /* Initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv,  iv.size());
    
    this->key=key;
    this->iv=iv;
}
