/**
 * @file ChaChaWrappers.hpp
 * @brief This module provides the declaration of the ChaCha20 class 
 * @author Iole Bolognesi 
 *
 * This module declares the ChaCha20 class.
 * The class declared is a concrete implementation of the Cipher class. 
 * It overrides the createEncryptor and createDecryptor methods. 
 *
 **/
#ifndef HEADER_CHACHAWRAPPER
#define HEADER_CHACHAWRAPPER

#include "Cipher.hpp"

/**
 * @brief Declares ChaCha20 class.
 */
class ChaChaAlias: public Cipher 
{
    public: 
        ChaChaAlias(int n_key_bytes = N_KEY_BYTES);

        cryptoTypes::Encryptor createEncryptor() override;

        cryptoTypes::Decryptor createDecryptor() override;
};
#endif