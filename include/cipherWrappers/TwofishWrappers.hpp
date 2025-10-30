/**
 * @file TwofishWrappers.hpp
 * @brief This module provides the declaration of TWOFISH classes 
 * @author Iole Bolognesi 
 *
 * This module declares one TWOFISH class per encryption mode. 
 * Each class declared is a concrete implementation of the Cipher class. 
 * createEncryptor and createDecryptor methods are overridden by all classes.
 * On the other hand, the requiresPadding method is ovverriden only by 
 * CBC and ECB classes which return true rather than false. 
 *
 **/
#ifndef HEADER_TWOFISHWRAPPERS
#define HEADER_TWOFISHWRAPPERS

#include "Cipher.hpp"

/**
 * @brief Declares TWOFISH-CBC class.
 */
class TwofishCbc : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares TWOFISH-ECB class.
 */
class TwofishEcb : public Cipher
{
    public:
        TwofishEcb(int n_key_bytes = N_KEY_BYTES); 

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
        
        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares TWOFISH-CFB class.
 */
class TwofishCfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares TWOFISH-OFB class.
 */
class TwofishOfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares TWOFISH-CTR class.
 */
class TwofishCtr : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

#endif
