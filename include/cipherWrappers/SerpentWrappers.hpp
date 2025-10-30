/**
 * @file SerpentWrappers.hpp
 * @brief This module provides the declaration of SERPENT classes 
 * @autor Iole Bolognesi 
 *
 * This module declares one SERPENT class per encryption mode. 
 * Each class declared is a concrete implementation of the Cipher class. 
 * createEncryptor and createDecryptor methods are overridden by all classes.
 * On the other hand, the requiresPadding method is ovverriden only by 
 * CBC and ECB classes which return true rather than false. 
 *
 **/
#ifndef HEADER_SERPENTWRAPPER
#define HEADER_SERPENTWRAPPER

#include "Cipher.hpp"

/**
 * @brief Declares SERPENT-CBC class.
 */
class SerpentCbc : public Cipher 
{
    public: 
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares SERPENT-ECB class.
 */
class SerpentEcb : public Cipher
{
    public:
        SerpentEcb(int n_key_bytes = N_KEY_BYTES);

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;

        bool requiresPadding() override { return true; }
};

/**
 * @brief Declares SERPENT-CFB class.
 */
class SerpentCfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares SERPENT-OFB class.
 */
class SerpentOfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

/**
 * @brief Declares SERPENT-CTR class.
 */
class SerpentCtr : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};

#endif
