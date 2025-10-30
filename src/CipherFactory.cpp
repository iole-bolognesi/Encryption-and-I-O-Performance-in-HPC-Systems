/**
 * @file CipherFactory.cpp
 * @brief This module provides the factory method for constructing 
 * objects of the derived classes that implement the Cipher class. 
 * @author Iole Bolognesi 
 **/

#include "CipherFactory.hpp"
#include "AesWrappers.hpp"
#include "ChaChaWrappers.hpp"
#include "MarsWrappers.hpp"
#include "RC6Wrappers.hpp"
#include "SerpentWrappers.hpp"
#include "TwofishWrappers.hpp"

/**
 * @brief Creates a concrete Cipher class for the input CipherType.
 *
 * This function constructs and returns a unique pointer to the Cipher class
 * that corresponds to the input CipherType. The supported algorithms 
 * and modes are:
 *   - `AES`, Serpent, Twofish, RC6, MARS (block ciphers), 
 *      and ChaCha20 (stream cipher)
 *   - CBC, CFB, OFB, CTR, ECB for block ciphers
 *
 * @param type The CipherType enum of the desired concrete Cipher class 
 *
 * @return std::unique_ptr<Cipher> to the requested cipher class;
 *         nullptr if `type` is unrecognized.
 */
std::unique_ptr<Cipher> CipherFactory::createCipher(CipherType type)
    {
        switch (type)
        {
            /* ---------- AES ---------- */
            case AES_CBC:    return std::make_unique<AesCbc>();
            case AES_CFB:    return std::make_unique<AesCfb>();
            case AES_OFB:    return std::make_unique<AesOfb>();
            case AES_CTR:    return std::make_unique<AesCtr>();
            case AES_ECB:    return std::make_unique<AesEcb>();

            /* ------- SERPENT --------- */
            case Serpent_CBC:  return std::make_unique<SerpentCbc>();
            case Serpent_CFB:  return std::make_unique<SerpentCfb>();
            case Serpent_OFB:  return std::make_unique<SerpentOfb>();
            case Serpent_CTR:  return std::make_unique<SerpentCtr>();
            case Serpent_ECB:  return std::make_unique<SerpentEcb>();

            /* ------- TWOFISH --------- */
            case Twofish_CBC:  return std::make_unique<TwofishCbc>();
            case Twofish_CFB:  return std::make_unique<TwofishCfb>();
            case Twofish_OFB:  return std::make_unique<TwofishOfb>();
            case Twofish_CTR:  return std::make_unique<TwofishCtr>();
            case Twofish_ECB:  return std::make_unique<TwofishEcb>();
            
            /* -------- RC6 ----------- */
            case RC6_CBC:      return std::make_unique<RC6Cbc>();
            case RC6_CFB:      return std::make_unique<RC6Cfb>();
            case RC6_OFB:      return std::make_unique<RC6Ofb>();
            case RC6_CTR:      return std::make_unique<RC6Ctr>();
            case RC6_ECB:      return std::make_unique<RC6Ecb>();

            /* -------- MARS ---------- */
            case Mars_CBC:     return std::make_unique<MarsCbc>(56);
            case Mars_CFB:     return std::make_unique<MarsCfb>(56);
            case Mars_OFB:     return std::make_unique<MarsOfb>(56);
            case Mars_CTR:     return std::make_unique<MarsCtr>(56);
            case Mars_ECB:     return std::make_unique<MarsEcb>(56);


            /* ------ CHACHA20 -------- */
            case ChaCha20:     return std::make_unique<ChaChaAlias>();
        }

        return nullptr;
    }