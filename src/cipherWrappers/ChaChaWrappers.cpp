/**
 * @file ChaChaWrappers.cpp
 * @brief This module provides the implementations of the ChaCha20 class
 * @author Iole Bolognesi
 *
 * This module provides the constructors of ChaCha20 class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects. 
 *
 **/
#include "ChaChaWrappers.hpp"

using namespace CryptoPP;

ChaChaAlias::ChaChaAlias(int n_key_bytes){

    SecByteBlock key(n_key_bytes);
    SecByteBlock iv(12);
    
    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv,  iv.size());
    
    this->key=key;
    this->iv=iv;
}

/**
 * @brief Creates a Crypto++ ChaCha encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ChaCha::Encryption object.
 */
cryptoTypes::Encryptor ChaChaAlias::createEncryptor() {
    auto encryptor = std::make_unique<ChaCha::Encryption>();
    encryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ ChaCha decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ChaCha::Decryption object.
 */
cryptoTypes::Decryptor ChaChaAlias::createDecryptor() {
    auto decryptor = std::make_unique<ChaCha::Decryption>();
    decryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return decryptor;
}