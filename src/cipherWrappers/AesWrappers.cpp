/**
 * @file AesWrappers.cpp
 * @brief This module provides the implementations of AES classes 
 * @author Iole Bolognesi
 *
 * This module provides the constructors of AES ECB class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects for all AES classes. 
 *
 **/

#include "AesWrappers.hpp"

#include <osrng.h>

using namespace CryptoPP;

/* -------------------------------- CBC MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ AES-CBC encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CBC_Mode<AES>::Encryption object.
 */
cryptoTypes::Encryptor AesCbc::createEncryptor() {
    auto encryptor = std::make_unique<CBC_Mode<AES>::Encryption>();
    encryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ AES-CBC decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CBC_Mode<AES>::Decryption object.
 */
cryptoTypes::Decryptor AesCbc::createDecryptor() {
    auto decryptor = std::make_unique<CBC_Mode<AES>::Decryption>();
    decryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return decryptor;
}

/* -------------------------------- ECB MODE -------------------------------------*/

/**
 * @brief Constructs an AES-ECB class with a with a cryptographic key. 
 *
 * This function uses the Crypto++ library to constructs an AES-ECB object 
 * and initialize the class member key with randomly generated 
 * sequences of bytes. This class overrides the Cipher constructor because 
 * it does not use an IV.
 *
 * @param n_key_bytes  Desired key length in bytes. 
 */
AesEcb::AesEcb(int n_key_bytes){

    SecByteBlock key(N_KEY_BYTES);  

    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    
    this->key=key;
}

/**
 * @brief Creates a Crypto++ AES-ECB encryptor initialized with the 
 * key member of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ECB_Mode<AES>::Encryption object.
 */
cryptoTypes::Encryptor AesEcb::createEncryptor() {
    auto encryptor = std::make_unique<ECB_Mode<AES>::Encryption>();
    encryptor->SetKey(this->key, this->key.size());
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ AES-ECB decryptor initialized with the 
 * key member of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ECB_Mode<AES>::Decryption object.
 */
cryptoTypes::Decryptor AesEcb::createDecryptor() {
    auto decryptor = std::make_unique<ECB_Mode<AES>::Decryption>();
    decryptor->SetKey(this->key, this->key.size());
    return decryptor;
}

/* -------------------------------- CFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ AES-CFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CFB_Mode<AES>::Encryption object.
 */
cryptoTypes::Encryptor AesCfb::createEncryptor() {
    auto encryptor = std::make_unique<CFB_Mode<AES>::Encryption>();
    encryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ AES-CFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CFB_Mode<AES>::Decryption object.
 */
cryptoTypes::Decryptor AesCfb::createDecryptor() {
    auto decryptor = std::make_unique<CFB_Mode<AES>::Decryption>();
    decryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return decryptor;
}


/* -------------------------------- OFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ AES-OFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         OFB_Mode<AES>::Encryption object.
 */
cryptoTypes::Encryptor AesOfb::createEncryptor() {
    auto encryptor = std::make_unique<OFB_Mode<AES>::Encryption>();
    encryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ AES-OFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         OFB_Mode<AES>::Decryption object.
 */
cryptoTypes::Decryptor AesOfb::createDecryptor() {
    auto decryptor = std::make_unique<OFB_Mode<AES>::Decryption>();
    decryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return decryptor;
}


/* -------------------------------- CTR MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ AES-CTR encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CTR_Mode<AES>::Encryption object.
 */
cryptoTypes::Encryptor AesCtr::createEncryptor() {
    auto encryptor = std::make_unique<CTR_Mode<AES>::Encryption>();
    encryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return encryptor; 
}

/**
 * @brief Creates a Crypto++ AES-CTR decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CTR_Mode<AES>::Decryption object.
 */
cryptoTypes::Decryptor AesCtr::createDecryptor() {
    auto decryptor = std::make_unique<CTR_Mode<AES>::Decryption>();
    decryptor->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return decryptor;
}