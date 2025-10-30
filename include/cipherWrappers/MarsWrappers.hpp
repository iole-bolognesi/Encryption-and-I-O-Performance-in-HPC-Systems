/**
 * @file MarsWrappers.hpp
 * @brief This module provides the declaration of MARS classes 
 * @author Iole Bolognesi 
 *
 * This module declares one MARS class per encryption mode. 
 * Each class declared is a concrete implementation of the Cipher class. 
 * createEncryptor and createDecryptor methods are overridden by all classes.
 * On the other hand, the requiresPadding method is ovverriden only by 
 * CBC and ECB classes which return true rather than false. 
 *
 **/
#ifndef HEADER_MARSWRAPPERS
#define HEADER_MARSWRAPPERS

#include "Cipher.hpp"

/**
 * @brief Declares MARS-CBC class.
 */
class MarsCbc : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor()  override;

        cryptoTypes::Decryptor createDecryptor()  override;

        bool requiresPadding() override {return true;};
};

/**
 * @brief Declares MARS-ECB class.
 */
class MarsEcb : public Cipher
{
    public:
        MarsEcb(int n_key_bytes = 56);

        cryptoTypes::Encryptor createEncryptor()  override;

        cryptoTypes::Decryptor createDecryptor()  override;

        bool requiresPadding() override {return true;};
};

/**
 * @brief Declares MARS-CFB class.
 */
class MarsCfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor()  override;

        cryptoTypes::Decryptor createDecryptor()  override;
};

/**
 * @brief Declares MARS-OFB class.
 */
class MarsOfb : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor()  override;

        cryptoTypes::Decryptor createDecryptor()  override;
};

/**
 * @brief Declares MARS-CTR class.
 */
class MarsCtr : public Cipher
{
    public:
        using Cipher::Cipher;

        cryptoTypes::Encryptor createEncryptor()  override;

        cryptoTypes::Decryptor createDecryptor()  override;
};

#endif
