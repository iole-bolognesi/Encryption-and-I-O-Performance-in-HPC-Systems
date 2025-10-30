#include "Cipher.hpp"
/**
 * @file RC6Wrappers.hpp
 * @brief This module provides the declaration of RC6 classes 
 * @author Iole Bolognesi 
 *
 * This module declares one RC6 class per encryption mode. 
 * Each class declared is a concrete implementation of the Cipher class. 
 * createEncryptor and createDecryptor methods are overridden by all classes.
 * On the other hand, the requiresPadding method is ovverriden only by 
 * CBC and ECB classes which return true rather than false. 
 *
 **/
#ifndef HEADER_RC6WRAPPER
#define HEADER_RC6WRAPPER

#include "Cipher.hpp"

/**
 * @brief Declares RC6-CBC class.
 */
class RC6Cbc : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares RC6-ECB class.
 */
class RC6Ecb : public Cipher
{
    public:
        RC6Ecb(int n_key_bytes = N_KEY_BYTES);

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares RC6-CFB class.
 */
class RC6Cfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

};

/**
 * @brief Declares RC6-OFB class.
 */
class RC6Ofb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

};

/**
 * @brief Declares RC6-CTR class.
 */
class RC6Ctr : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};
#endif 