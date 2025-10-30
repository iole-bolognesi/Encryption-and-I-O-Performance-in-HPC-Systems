/**
 * @file AesWrappers.hpp
 * @brief This module provides the declaration of AES classes 
 * @author Iole Bolognesi 
 *
 * This module declares one AES class per encryption mode. 
 * Each class declared is a concrete implementation of the Cipher class. 
 * createEncryptor and createDecryptor methods are overridden by all classes.
 * On the other hand, the requiresPadding method is ovverriden only by 
 * CBC and ECB classes which return true rather than false. 
 *
 **/
#ifndef HEADER_AESWRAPPERS
#define HEADER_AESWRAPPERS

#include "Cipher.hpp"

/**
 * @brief Declares AES-CBC class.
 */
class AesCbc : public Cipher 
{
    public: 
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; };

};

/**
 * @brief Declares AES-ECB class.
 */
class AesEcb : public Cipher 
{
    public: 
        AesEcb(int n_key_bytes = N_KEY_BYTES);

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; };
};

/**
 * @brief Declares AES-CFB class.
 */
class AesCfb : public Cipher 
{
    public: 
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares AES-OFB class.
 */
class AesOfb : public Cipher 
{
    public: 
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares AES-CTR class.
 */
class AesCtr: public Cipher 
{
    public: 
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};
#endif