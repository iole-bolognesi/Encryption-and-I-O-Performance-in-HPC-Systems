/**
 * @file SerpentWrappers.cpp
 * @brief This module provides the implementations of SERPENT classes 
 * @author Iole Bolognesi
 *
 * This module provides the constructors of SERPENT ECB class as well as 
 * the implementation of member methods returning Crypto++ encryption
 * and decryption objects for all SERPENT classes. 
 *
 **/

#include "SerpentWrappers.hpp"

#include <osrng.h>

using namespace CryptoPP;

/* -------------------------------- CBC MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ SERPENT-CBC encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CBC_Mode<Serpent>::Encryption object.
 */
cryptoTypes::Encryptor SerpentCbc::createEncryptor(){
    auto enc = std::make_unique<CBC_Mode<Serpent>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ SERPENT-CBC decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CBC_Mode<Serpent>::Decryption object.
 */
cryptoTypes::Decryptor SerpentCbc::createDecryptor(){
    auto dec = std::make_unique<CBC_Mode<Serpent>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- ECB MODE -------------------------------------*/

/**
 * @brief Constructs an SERPENT-ECB class with a with a cryptographic key. 
 *
 * This function uses the Crypto++ library to constructs an SERPENT-ECB object 
 * and initialize the class member key with randomly generated 
 * sequences of bytes. This class overrides the Cipher constructor because 
 * it does not use an IV.
 *
 * @param n_key_bytes  Desired key length in bytes. 
 */
SerpentEcb::SerpentEcb(int n_key_bytes){
    
    SecByteBlock key(N_KEY_BYTES);  

    /* initialize key and iv with randomly 
    generated sequence of bytes */
    AutoSeededRandomPool prng;
    prng.GenerateBlock(key, key.size());
    
    this->key=key;
}

/**
 * @brief Creates a Crypto++ SERPENT-ECB encryptor initialized with the 
 * key member of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         ECB_Mode<Serpent>::Encryption object.
 */
cryptoTypes::Encryptor SerpentEcb::createEncryptor(){
    auto enc = std::make_unique<ECB_Mode<Serpent>::Encryption>();
    enc->SetKey(key, key.size());
    return enc;
}

/**
 * @brief Creates a Crypto++ SERPENT-ECB decryptor initialized with the 
 * key member of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         ECB_Mode<Serpent>::Decryption object.
 */
cryptoTypes::Decryptor SerpentEcb::createDecryptor(){
    auto dec = std::make_unique<ECB_Mode<Serpent>::Decryption>();
    dec->SetKey(key, key.size());
    return dec;
}

/* -------------------------------- CFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ SERPENT-CFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CFB_Mode<Serpent>::Encryption object.
 */
cryptoTypes::Encryptor SerpentCfb::createEncryptor(){
    auto enc = std::make_unique<CFB_Mode<Serpent>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ SERPENT-CFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CFB_Mode<Serpent>::Decryption object.
 */
cryptoTypes::Decryptor SerpentCfb::createDecryptor(){
    auto dec = std::make_unique<CFB_Mode<Serpent>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- OFB MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ SERPENT-OFB encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         OFB_Mode<Serpent>::Encryption object.
 */
cryptoTypes::Encryptor SerpentOfb::createEncryptor(){
    auto enc = std::make_unique<OFB_Mode<Serpent>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ SERPENT-OFB decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         OFB_Mode<Serpent>::Decryption object.
 */
cryptoTypes::Decryptor SerpentOfb::createDecryptor(){
    auto dec = std::make_unique<OFB_Mode<Serpent>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}

/* -------------------------------- CTR MODE -------------------------------------*/

/**
 * @brief Creates a Crypto++ SERPENT-CTR encryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return an Encryptor object that wraps the Crypto++
 *         CTR_Mode<Serpent>::Encryption object.
 */
cryptoTypes::Encryptor SerpentCtr::createEncryptor(){
    auto enc = std::make_unique<CTR_Mode<Serpent>::Encryption>();
    enc->SetKeyWithIV(key, key.size(), iv);
    return enc;
}

/**
 * @brief Creates a Crypto++ SERPENT-CTR decryptor initialized with the 
 * key and IV members of the class instance. 
 *
 * @return a Decryptor object that wraps the Crypto++
 *         CTR_Mode<Serpent>::Decryption object.
 */
cryptoTypes::Decryptor SerpentCtr::createDecryptor(){
    auto dec = std::make_unique<CTR_Mode<Serpent>::Decryption>();
    dec->SetKeyWithIV(key, key.size(), iv);
    return dec;
}
