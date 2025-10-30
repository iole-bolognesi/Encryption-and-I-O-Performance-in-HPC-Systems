/**
 * @file MarsWrappers.cpp
 * @brief This module provides the implementations of MARS classes 
 * @author Iole Bolognesi
 *
 * This module provides the constructors of MARS ECB class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects for all MARS classes. 
 *
 **/

#include "MarsWrappers.hpp" 

#include <osrng.h>
#include <iostream>

using namespace CryptoPP;

/* -------------------------------- CBC MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ MARS-CBC encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CBC_Mode<MARS>::Encryption object.
 */
cryptoTypes::Encryptor MarsCbc::createEncryptor(){
    auto enc = std::make_unique<CBC_Mode<MARS>::Encryption>();
    enc->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ MARS-CBC decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CBC_Mode<MARS>::Decryption object.
 */
cryptoTypes::Decryptor MarsCbc::createDecryptor(){
    auto dec = std::make_unique<CBC_Mode<MARS>::Decryption>();
    dec->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return dec;
}

/* -------------------------------- ECB MODE -------------------------------------*/

/**
 * @brief Constructs an MARS-ECB class with a with a cryptographic key. 
 *
 * This function uses the Crypto++ library to constructs an MARS-ECB object 
 * and initialize the class member key with randomly generated 
 * sequences of bytes. This class overrides the Cipher constructor because 
 * it does not use an IV.
 *
 * @param n_key_bytes  Desired key length in bytes. 
 */
MarsEcb::MarsEcb(int n_key_bytes){
    
    SecByteBlock key(n_key_bytes);  

    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    
    this->key=key;
}

/**
 * @brief Creates a Crypto++ MARS-ECB encryptor initialized with the 
 * key member of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ECB_Mode<MARS>::Encryption object.
 */
cryptoTypes::Encryptor MarsEcb::createEncryptor(){
    auto enc = std::make_unique<ECB_Mode<MARS>::Encryption>();
    enc->SetKey(this->key, this->key.size());
    return enc;
}

/**
 * @brief Creates a Crypto++ MARS-ECB decryptor initialized with the 
 * key member of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ECB_Mode<MARS>::Decryption object.
 */
cryptoTypes::Decryptor MarsEcb::createDecryptor(){
    auto dec = std::make_unique<ECB_Mode<MARS>::Decryption>();
    dec->SetKey(this->key, this->key.size());
    return dec;
}

/* -------------------------------- CFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ MARS-CFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CFB_Mode<MARS>::Encryption object.
 */
cryptoTypes::Encryptor MarsCfb::createEncryptor(){
    auto enc = std::make_unique<CFB_Mode<MARS>::Encryption>();
    enc->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ MARS-CFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CFB_Mode<MARS>::Decryption object.
 */
cryptoTypes::Decryptor MarsCfb::createDecryptor(){
    auto dec = std::make_unique<CFB_Mode<MARS>::Decryption>();
    dec->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return dec;
}

/* -------------------------------- OFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ MARS-OFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         OFB_Mode<MARS>::Encryption object.
 */
cryptoTypes::Encryptor MarsOfb::createEncryptor(){
    auto enc = std::make_unique<OFB_Mode<MARS>::Encryption>();
    enc->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ MARS-OFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         OFB_Mode<MARS>::Decryption object.
 */
cryptoTypes::Decryptor MarsOfb::createDecryptor(){
    auto dec = std::make_unique<OFB_Mode<MARS>::Decryption>();
    dec->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return dec;
}

/* -------------------------------- CTR MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ MARS-CTR encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CTR_Mode<MARS>::Encryption object.
 */
cryptoTypes::Encryptor MarsCtr::createEncryptor(){
    auto enc = std::make_unique<CTR_Mode<MARS>::Encryption>();
    enc->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ MARS-CTR decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CTR_Mode<MARS>::Decryption object.
 */
cryptoTypes::Decryptor MarsCtr::createDecryptor(){
    auto dec = std::make_unique<CTR_Mode<MARS>::Decryption>();
    dec->SetKeyWithIV(this->key, this->key.size(), this->iv);
    return dec;
}
