/**
 * @file TwofishWrappers.cpp
 * @brief This module provides the implementations of TWOFISH classes 
 * @author Iole Bolognesi
 *
 * This module provides the constructors of TWOFISH ECB class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects for all TWOFISH classes. 
 *
 **/

#include "TwofishWrappers.hpp"

#include <osrng.h>

using namespace CryptoPP;

/* -------------------------------- CBC MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ TWOFISH-CBC encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CBC_Mode<Twofish>::Encryption object.
 */
cryptoTypes::Encryptor TwofishCbc::createEncryptor(){
    auto encryptor = std::make_unique<CBC_Mode<Twofish>::Encryption>();
    encryptor->SetKeyWithIV(key, key.size(), iv);
    return encryptor;
}

/**
 * @brief Creates a Crypto++ TWOFISH-CBC decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CBC_Mode<Twofish>::Decryption object.
 */
cryptoTypes::Decryptor TwofishCbc::createDecryptor(){
    auto decryptor = std::make_unique<CBC_Mode<Twofish>::Decryption>();
    decryptor->SetKeyWithIV(key, key.size(), iv);
    return decryptor;
}

/* -------------------------------- ECB MODE -------------------------------------*/

/**
 * @brief Constructs an TWOFISH-ECB class with a with a cryptographic key. 
 *
 * This function uses the Crypto++ library to constructs an TWOFISH-ECB object 
 * and initialize the class member key with randomly generated 
 * sequences of bytes. This class overrides the Cipher constructor because 
 * it does not use an IV.
 *
 * @param n_key_bytes  Desired key length in bytes. 
 */
TwofishEcb::TwofishEcb(int n_key_bytes){

    SecByteBlock key(N_KEY_BYTES);  

    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    
    this->key=key;
}

/**
 * @brief Creates a Crypto++ TWOFISH-ECB encryptor initialized with the 
 * key member of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ECB_Mode<Twofish>::Encryption object.
 */
cryptoTypes::Encryptor TwofishEcb::createEncryptor(){
    auto encryptor = std::make_unique<ECB_Mode<Twofish>::Encryption>();
    encryptor->SetKey(key, key.size());
    return encryptor;
}

/**
 * @brief Creates a Crypto++ TWOFISH-ECB decryptor initialized with the 
 * key member of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ECB_Mode<Twofish>::Decryption object.
 */
cryptoTypes::Decryptor TwofishEcb::createDecryptor(){
    auto decryptor = std::make_unique<ECB_Mode<Twofish>::Decryption>();
    decryptor->SetKey(key, key.size());
    return decryptor;
}

/* -------------------------------- CFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ TWOFISH-CFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CFB_Mode<Twofish>::Encryption object.
 */
cryptoTypes::Encryptor TwofishCfb::createEncryptor(){
    auto encryptor = std::make_unique<CFB_Mode<Twofish>::Encryption>();
    encryptor->SetKeyWithIV(key, key.size(), iv);
    return encryptor;
}

/**
 * @brief Creates a Crypto++ TWOFISH-CFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CFB_Mode<Twofish>::Decryption object.
 */
cryptoTypes::Decryptor TwofishCfb::createDecryptor(){
    auto decryptor = std::make_unique<CFB_Mode<Twofish>::Decryption>();
    decryptor->SetKeyWithIV(key, key.size(), iv);
    return decryptor;
}

/* -------------------------------- OFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ TWOFISH-OFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         OFB_Mode<Twofish>::Encryption object.
 */
cryptoTypes::Encryptor TwofishOfb::createEncryptor(){
    auto encryptor = std::make_unique<OFB_Mode<Twofish>::Encryption>();
    encryptor->SetKeyWithIV(key, key.size(), iv);
    return encryptor;
}

/**
 * @brief Creates a Crypto++ TWOFISH-OFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         OFB_Mode<Twofish>::Decryption object.
 */
cryptoTypes::Decryptor TwofishOfb::createDecryptor(){
    auto decryptor = std::make_unique<OFB_Mode<Twofish>::Decryption>();
    decryptor->SetKeyWithIV(key, key.size(), iv);
    return decryptor;
}

/* -------------------------------- CTR MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ TWOFISH-CTR encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CTR_Mode<Twofish>::Encryption object.
 */
cryptoTypes::Encryptor TwofishCtr::createEncryptor(){
    auto encryptor = std::make_unique<CTR_Mode<Twofish>::Encryption>();
    encryptor->SetKeyWithIV(key, key.size(), iv);
    return encryptor;
}

/**
 * @brief Creates a Crypto++ TWOFISH-CTR decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CTR_Mode<Twofish>::Decryption object.
 */
cryptoTypes::Decryptor TwofishCtr::createDecryptor(){
    auto decryptor = std::make_unique<CTR_Mode<Twofish>::Decryption>();
    decryptor->SetKeyWithIV(key, key.size(), iv);
    return decryptor;
}
