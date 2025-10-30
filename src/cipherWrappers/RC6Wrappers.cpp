/**
 * @file RC6Wrappers.cpp
 * @brief This module provides the implementations of RC6 classes 
 * @author Iole Bolognesi
 *
 * This module provides the constructors of RC6 ECB class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects for all RC6 classes. 
 *
 **/

#include "RC6Wrappers.hpp"

#include <osrng.h>

using namespace CryptoPP;

/* -------------------------------- CBC MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ RC6-CBC encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CBC_Mode<RC6>::Encryption object.
 */
cryptoTypes::Encryptor RC6Cbc::createEncryptor()
{
    auto enc = std::make_unique<CBC_Mode<RC6>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ RC6-CBC decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CBC_Mode<RC6>::Decryption object.
 */
cryptoTypes::Decryptor RC6Cbc::createDecryptor()
{
    auto dec = std::make_unique<CBC_Mode<RC6>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- ECB MODE -------------------------------------*/

/**
 * @brief Constructs an RC6-ECB class with a with a cryptographic key. 
 *
 * This function uses the Crypto++ library to constructs an RC6-ECB object 
 * and initialize the class member key with randomly generated 
 * sequences of bytes. This class overrides the Cipher constructor because 
 * it does not use an IV.
 *
 * @param n_key_bytes  Desired key length in bytes. 
 */
RC6Ecb::RC6Ecb(int n_key_bytes){
    
    SecByteBlock key(N_KEY_BYTES);  

    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    
    this->key=key;
}

/**
 * @brief Creates a Crypto++ RC6-ECB encryptor initialized with the 
 * key member of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ECB_Mode<RC6>::Encryption object.
 */
cryptoTypes::Encryptor RC6Ecb::createEncryptor(){
    auto enc = std::make_unique<ECB_Mode<RC6>::Encryption>();
    enc->SetKey(key, key.size());
    return enc;
}

/**
 * @brief Creates a Crypto++ RC6-ECB decryptor initialized with the 
 * key member of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ECB_Mode<RC6>::Decryption object.
 */
cryptoTypes::Decryptor RC6Ecb::createDecryptor(){
    auto dec = std::make_unique<ECB_Mode<RC6>::Decryption>();
    dec->SetKey(key, key.size());
    return dec;
}

/* -------------------------------- CFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ RC6-CFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CFB_Mode<RC6>::Encryption object.
 */
cryptoTypes::Encryptor RC6Cfb::createEncryptor(){
    auto enc = std::make_unique<CFB_Mode<RC6>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ RC6-CFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CFB_Mode<RC6>::Decryption object.
 */
cryptoTypes::Decryptor RC6Cfb::createDecryptor(){
    auto dec = std::make_unique<CFB_Mode<RC6>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- OFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ RC6-OFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         OFB_Mode<RC6>::Encryption object.
 */
cryptoTypes::Encryptor RC6Ofb::createEncryptor(){
    auto enc = std::make_unique<OFB_Mode<RC6>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ RC6-OFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         OFB_Mode<RC6>::Decryption object.
 */
cryptoTypes::Decryptor RC6Ofb::createDecryptor(){
    auto dec = std::make_unique<OFB_Mode<RC6>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- CTR MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ RC6-CTR encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CTR_Mode<RC6>::Encryption object.
 */
cryptoTypes::Encryptor RC6Ctr::createEncryptor(){
    auto enc = std::make_unique<CTR_Mode<RC6>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ RC6-CTR decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CTR_Mode<RC6>::Decryption object.
 */
cryptoTypes::Decryptor RC6Ctr::createDecryptor(){
    auto dec = std::make_unique<CTR_Mode<RC6>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}
