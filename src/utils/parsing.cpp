/** 
* @file parsing.cpp
* @brief This module defines a function to convert a string to a 
* CyperType enum (defined in file CipherFactory.hpp)
* @author Iole Bolognesi 
* 
*/

#include "parsing.hpp"
#include "CipherFactory.hpp"

/**
 * @brief Converts a string to its corresponding CipherType enum value.
 *
 * This function returns the CipherType enum corresponding to the
 * input cipher name. If the given string does not match any valid cipher, 
 * the function prints an error message and terminates the program. 
 *
 * @param input  Cipher name string to be converted.
 * @param rank   MPI rank of the calling process
 * @return The   corresponding CipherType enumeration constant.
 */
CipherType getEnumFromString(std::string_view input,int rank) {

    /* ---------- AES ---------- */
    if (input == "AES_CBC")         return AES_CBC;
    if (input == "AES_CFB")         return AES_CFB;
    if (input == "AES_OFB")         return AES_OFB;
    if (input == "AES_CTR")         return AES_CTR;
    if (input == "AES_ECB")         return AES_ECB;

    /* ------- SERPENT --------- */
    if (input == "SERPENT_CBC")     return Serpent_CBC;
    if (input == "SERPENT_CFB")     return Serpent_CFB;
    if (input == "SERPENT_OFB")     return Serpent_OFB;
    if (input == "SERPENT_CTR")     return Serpent_CTR;
    if (input == "SERPENT_ECB")     return Serpent_ECB;

     /* -------- MARS ---------- */
    if (input == "MARS_CBC")        return Mars_CBC;
    if (input == "MARS_CFB")        return Mars_CFB;
    if (input == "MARS_OFB")        return Mars_OFB;
    if (input == "MARS_CTR")        return Mars_CTR;
    if (input == "MARS_ECB")        return Mars_ECB;

    /* -------- RC6 ----------- */
    if (input == "RC6_CBC")         return RC6_CBC;
    if (input == "RC6_CFB")         return RC6_CFB;
    if (input == "RC6_OFB")         return RC6_OFB;
    if (input == "RC6_CTR")         return RC6_CTR;
    if (input == "RC6_ECB")         return RC6_ECB;

    /* ------- TWOFISH --------- */
    if (input == "TWOFISH_CBC")     return Twofish_CBC;
    if (input == "TWOFISH_CFB")     return Twofish_CFB;
    if (input == "TWOFISH_OFB")     return Twofish_OFB;
    if (input == "TWOFISH_CTR")     return Twofish_CTR;
    if (input == "TWOFISH_ECB")     return Twofish_ECB;

    /* ------ CHACHA20 -------- */
    if (input == "CHACHA20")        return ChaCha20;

    if(rank==0){
        std::cerr << "You entered an invalid cipher: " << input << std::endl;
        std::cerr << "VALID CIPHERS ARE:" << std::endl;
        
        std::cerr << "AES_CBC" << std::endl;
        std::cerr << "AES_CFB" << std::endl;
        std::cerr << "AES_OFB" << std::endl;
        std::cerr << "AES_CTR" << std::endl;
        std::cerr << "AES_ECB" << std::endl;

        std::cerr << "SERPENT_CBC" << std::endl;
        std::cerr << "SERPENT_CFB" << std::endl;
        std::cerr << "SERPENT_OFB" << std::endl;
        std::cerr << "SERPENT_CTR" << std::endl;
        std::cerr << "SERPENT_ECB" << std::endl;

        std::cerr << "MARS_CBC" << std::endl;
        std::cerr << "MARS_CFB" << std::endl;
        std::cerr << "MARS_OFB" << std::endl;
        std::cerr << "MARS_CTR" << std::endl;
        std::cerr << "MARS_ECB" << std::endl;

        std::cerr << "RC6_CBC" << std::endl;
        std::cerr << "RC6_CFB" << std::endl;
        std::cerr << "RC6_OFB" << std::endl;
        std::cerr << "RC6_CTR" << std::endl;
        std::cerr << "RC6_ECB" << std::endl;

        std::cerr << "TWOFISH_CBC" << std::endl;
        std::cerr << "TWOFISH_CFB" << std::endl;
        std::cerr << "TWOFISH_OFB" << std::endl;
        std::cerr << "TWOFISH_CTR" << std::endl;
        std::cerr << "TWOFISH_ECB" << std::endl;

        std::cerr << "CHACHA20" << std::endl;
    }
    std::exit(1);
}