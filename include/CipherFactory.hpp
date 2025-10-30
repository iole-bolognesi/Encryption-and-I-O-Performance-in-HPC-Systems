/**
 * @file CipherFactory.hpp
 * @brief This module declares the CipherFactory class and the CipherType enum
 * @author Iole Bolognesi
 *
 * This module declares the CipherType enumeration and a factory class to construct
 * concrete Cipher implementations based on a CipherType input value.
 */

#ifndef HEADER_CIPHERFACTORY
#define HEADER_CIPHERFACTORY

#include "Cipher.hpp"

enum CipherType {
    AES_CBC, AES_CFB, AES_OFB, AES_CTR, AES_ECB,
    Serpent_CBC, Serpent_CFB, Serpent_OFB, Serpent_CTR, Serpent_ECB,
    Twofish_CBC, Twofish_CFB, Twofish_OFB, Twofish_CTR, Twofish_ECB,
    Mars_CBC, Mars_CFB, Mars_OFB, Mars_CTR, Mars_ECB,
    RC6_CBC, RC6_CFB, RC6_OFB, RC6_CTR, RC6_ECB,
    ChaCha20
};

/**
 * @brief Declares factory class. 
 */
class CipherFactory
{
    public:
        std::unique_ptr<Cipher> createCipher(CipherType type);
    };
#endif 
