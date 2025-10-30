/**
 * @file Cipher.hpp
 * @brief This module declares the base Cipher interface and type aliases for 
 * Crypto++ encryption and decryption objects. 
 * @author Iole Bolognesi
 *
 * This module declares the Cipher class with virtual methods and aggregates 
 * Crypto++ mode-specific type aliases into Encryptor/Decryptor variants.
 **/

#ifndef HEADER_CIPHERCLASS
#define HEADER_CIPHERCLASS

#include <serpent.h>
#include <aes.h>
#include <twofish.h>
#include <mars.h>
#include <rc6.h>
#include <chacha.h>
#include <modes.h>
#include <variant> 
#include <osrng.h>

#define N_BLOCK_BYTES 16
#define N_KEY_BYTES 32

namespace cryptoTypes
{
    /* AES */ 
    using EncAesCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption>;
    using DecAesCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption>;

    using EncAesCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption>;
    using DecAesCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption>;

    using EncAesOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption>;
    using DecAesOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::AES>::Decryption>;

    using EncAesCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption>;
    using DecAesCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption>;

    using EncAesEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption>;
    using DecAesEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption>;

    /* Serpent */
    using EncSerpentCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::Serpent>::Encryption>;
    using DecSerpentCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::Serpent>::Decryption>;

    using EncSerpentCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::Serpent>::Encryption>;
    using DecSerpentCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::Serpent>::Decryption>;

    using EncSerpentOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::Serpent>::Encryption>;
    using DecSerpentOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::Serpent>::Decryption>;

    using EncSerpentCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::Serpent>::Encryption>;
    using DecSerpentCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::Serpent>::Decryption>;

    using EncSerpentEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::Serpent>::Encryption>;
    using DecSerpentEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::Serpent>::Decryption>;

    /* Twofish */ 
    using EncTwofishCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::Twofish>::Encryption>;
    using DecTwofishCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::Twofish>::Decryption>;

    using EncTwofishCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::Twofish>::Encryption>;
    using DecTwofishCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::Twofish>::Decryption>;

    using EncTwofishOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::Twofish>::Encryption>;
    using DecTwofishOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::Twofish>::Decryption>;

    using EncTwofishCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::Twofish>::Encryption>;
    using DecTwofishCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::Twofish>::Decryption>;

    using EncTwofishEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::Twofish>::Encryption>;
    using DecTwofishEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::Twofish>::Decryption>;

    /* Mars */  
    using EncMarsCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::MARS>::Encryption>;
    using DecMarsCbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::MARS>::Decryption>;

    using EncMarsCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::MARS>::Encryption>;
    using DecMarsCfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::MARS>::Decryption>;

    using EncMarsOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::MARS>::Encryption>;
    using DecMarsOfb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::MARS>::Decryption>;

    using EncMarsCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::MARS>::Encryption>;
    using DecMarsCtr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::MARS>::Decryption>;

    using EncMarsEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::MARS>::Encryption>;
    using DecMarsEcb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::MARS>::Decryption>;

    /* RC6 */  
    using EncRC6Cbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::RC6>::Encryption>;
    using DecRC6Cbc = std::unique_ptr<CryptoPP::CBC_Mode<CryptoPP::RC6>::Decryption>;

    using EncRC6Cfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::RC6>::Encryption>;
    using DecRC6Cfb = std::unique_ptr<CryptoPP::CFB_Mode<CryptoPP::RC6>::Decryption>;

    using EncRC6Ofb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::RC6>::Encryption>;
    using DecRC6Ofb = std::unique_ptr<CryptoPP::OFB_Mode<CryptoPP::RC6>::Decryption>;

    using EncRC6Ctr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::RC6>::Encryption>;
    using DecRC6Ctr = std::unique_ptr<CryptoPP::CTR_Mode<CryptoPP::RC6>::Decryption>;

    using EncRC6Ecb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::RC6>::Encryption>;
    using DecRC6Ecb = std::unique_ptr<CryptoPP::ECB_Mode<CryptoPP::RC6>::Decryption>;

    /* ChaCha */  
    using EncChaCha = std::unique_ptr<CryptoPP::ChaCha::Encryption>;  
    using DecChaCha = std::unique_ptr<CryptoPP::ChaCha::Encryption>;

    using Encryptor = std::variant<
        EncAesCbc, EncAesCfb, EncAesOfb, EncAesCtr, EncAesEcb,
        EncSerpentCbc, EncSerpentCfb, EncSerpentOfb, EncSerpentCtr, EncSerpentEcb,
        EncTwofishCbc, EncTwofishCfb, EncTwofishOfb, EncTwofishCtr, EncTwofishEcb,
        EncMarsCbc, EncMarsCfb, EncMarsOfb, EncMarsCtr, EncMarsEcb,
        EncRC6Cbc, EncRC6Cfb, EncRC6Ofb, EncRC6Ctr, EncRC6Ecb,
        EncChaCha
    >;

    using Decryptor = std::variant<
        DecAesCbc, DecAesCfb, DecAesOfb, DecAesCtr, DecAesEcb,
        DecSerpentCbc, DecSerpentCfb, DecSerpentOfb, DecSerpentCtr, DecSerpentEcb,
        DecTwofishCbc, DecTwofishCfb, DecTwofishOfb, DecTwofishCtr, DecTwofishEcb,
        DecMarsCbc, DecMarsCfb, DecMarsOfb, DecMarsCtr, DecMarsEcb,
        DecRC6Cbc, DecRC6Cfb, DecRC6Ofb, DecRC6Ctr, DecRC6Ecb,
        DecChaCha
    >;
}

/**
 * @brief Declares Cipher interface class.
 */
class Cipher
{
    protected:
        CryptoPP::SecByteBlock key;
        CryptoPP::SecByteBlock iv;
    
    public: 
        Cipher(int n_key_bytes = N_KEY_BYTES);
        virtual ~Cipher() = default;
        virtual cryptoTypes::Encryptor createEncryptor()=0;
        virtual cryptoTypes::Decryptor createDecryptor()=0;
        virtual bool requiresPadding() { return false; };
};
#endif