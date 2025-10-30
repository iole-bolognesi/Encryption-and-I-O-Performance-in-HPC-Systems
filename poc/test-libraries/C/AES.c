/**
 * @file AES.c
 * @brief This program encrypts and decrypts a file using OpenSSL's EVP API with AES-256-CBC.
 *
 * This implementation was taken and adapted from:
 * https://medium.com/@amit.kulkarni/encrypting-decrypting-a-file-using-openssl-evp-b26e0e4d28d4
 *
 * The program generates a random AES key and IV, encrypts a given file,
 * and decrypts it back. The program's intent is to test the OpenSSL library. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include "AES.h"

/**
 * @brief Cleans up resources and exits the program.
 * @param params Cipher parameters
 * @param ifp Pointer to input file
 * @param ofp Pointer to output file 
 * @param rc Return code
 */

void cleanup(cipher_params_t *params, FILE *ifp, FILE *ofp, int rc){
    free(params);
    fclose(ifp);
    fclose(ofp);
    exit(rc);
}

/** 
 * Checks if a directory exists and creates it if it does not. 
 *
 * @param path Reference to directory path.
 */
 void ensure_directory_exists(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        printf("\nCreating directory: %s\n", path);
        if (mkdir(path, 0777) != 0) {
            perror("mkdir failed");
        }
    }
}

/**
 * @brief Encrypts or decrypts a file using AES-256-CBC.
 * @param params Cipher parameters
 * @param ifp Pointer to input file
 * @param ofp Pointer to output file 
 */

void file_encrypt_decrypt(cipher_params_t *params, FILE *ifp, FILE *ofp){
    
    /* Allow enough space in output buffer for additional block */
    int cipher_block_size = EVP_CIPHER_block_size(params->cipher_type);
    unsigned char in_buf[BUFSIZE], out_buf[BUFSIZE + cipher_block_size];

    int num_bytes_read, out_len;
    EVP_CIPHER_CTX * ctx;

    ctx = EVP_CIPHER_CTX_new();
    if(ctx == NULL){
        fprintf(stderr, "ERROR: EVP_CIPHER_CTX_new failed. OpenSSL error: %s\n", 
                ERR_error_string(ERR_get_error(), NULL));
        cleanup(params, ifp, ofp, ERR_EVP_CTX_NEW);
    }

    if(!EVP_CipherInit_ex(ctx, params->cipher_type, NULL, NULL, NULL, params->encrypt)){
        fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n", 
                ERR_error_string(ERR_get_error(), NULL));
        cleanup(params, ifp, ofp, ERR_EVP_CIPHER_INIT);
    }

     /* Check lengths */
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == AES_256_KEY_SIZE);
    OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);

    /* Set key and IV */
    if(!EVP_CipherInit_ex(ctx, NULL, NULL, params->key, params->iv, params->encrypt)){
        fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n", 
                ERR_error_string(ERR_get_error(), NULL));
        EVP_CIPHER_CTX_cleanup(ctx);
        cleanup(params, ifp, ofp, ERR_EVP_CIPHER_INIT);
    }

    while(1){

        /* Read in data in blocks until EOF. Update the ciphering with each read.*/

        num_bytes_read = fread(in_buf, sizeof(unsigned char), BUFSIZE, ifp);
        if (ferror(ifp)){
            fprintf(stderr, "ERROR: fread error: %s\n", strerror(errno));
            EVP_CIPHER_CTX_cleanup(ctx);
            cleanup(params, ifp, ofp, errno);
        }
        if(!EVP_CipherUpdate(ctx, out_buf, &out_len, in_buf, num_bytes_read)){
            fprintf(stderr, "ERROR: EVP_CipherUpdate failed. OpenSSL error: %s\n", 
                    ERR_error_string(ERR_get_error(), NULL));
            EVP_CIPHER_CTX_cleanup(ctx);
            cleanup(params, ifp, ofp, ERR_EVP_CIPHER_UPDATE);
        }

        fwrite(out_buf, sizeof(unsigned char), out_len, ofp);

        if (ferror(ofp)) {
            fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
            EVP_CIPHER_CTX_cleanup(ctx);
            cleanup(params, ifp, ofp, errno);
        }
        if (num_bytes_read < BUFSIZE) {
            break;
        }
    }

    /* Now cipher the final block and write it out to file */

    if(!EVP_CipherFinal_ex(ctx, out_buf, &out_len)){
        fprintf(stderr, "ERROR: EVP_CipherFinal_ex failed. OpenSSL error: %s\n", 
                ERR_error_string(ERR_get_error(), NULL));
        EVP_CIPHER_CTX_cleanup(ctx);
        cleanup(params, ifp, ofp, ERR_EVP_CIPHER_FINAL);
    }
    fwrite(out_buf, sizeof(unsigned char), out_len, ofp);
    if (ferror(ofp)) {
        fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
        EVP_CIPHER_CTX_cleanup(ctx);
        cleanup(params, ifp, ofp, errno);
    }
    EVP_CIPHER_CTX_cleanup(ctx);
}

int main(int argc, char *argv[]) {
    
    FILE *f_input, *f_enc, *f_dec;    

    cipher_params_t *params = (cipher_params_t *) malloc(sizeof(cipher_params_t));
    if (!params) {
        fprintf(stderr, "ERROR: malloc error: %s\n", strerror(errno));
        return errno;
    };

    /* Key to use for encrpytion and decryption */
    unsigned char key[AES_256_KEY_SIZE];

    /* Initialization Vector */
    unsigned char iv[AES_BLOCK_SIZE];

    /* Generate cryptographically strong pseudo-random bytes for key and IV */
    if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
        fprintf(stderr, "ERROR: RAND_bytes error: %s\n", strerror(errno));
        return errno;
    };

    params->key = key;
    params->iv = iv;

    /* Indicate that we want to encrypt */
    params->encrypt = 1;

    /* Set the cipher type and mode*/
    params->cipher_type = EVP_aes_256_cbc();

    ensure_directory_exists("./input/");
    f_input = fopen("./input/signature", "rb");
    if (!f_input) {
        fprintf(stderr, "ERROR: fopen error: %s\n", strerror(errno));
        return errno;
    };

    ensure_directory_exists("output/OpenSSL/");

    f_enc = fopen("output/OpenSSL/encrypted_file", "wb");
    if (!f_enc) {
        fprintf(stderr, "ERROR: fopen error: %s\n", strerror(errno));
        return errno;
    };

    /* Encrypt */
    file_encrypt_decrypt(params, f_input, f_enc);
    fclose(f_input);
    fclose(f_enc);

    /* Indicate that we want to decrypt */
    params->encrypt = 0;

    f_input = fopen("output/OpenSSL/encrypted_file", "rb");
    if (!f_input) {
        fprintf(stderr, "ERROR: fopen error: %s\n", strerror(errno));
        return errno;
    };


    f_dec = fopen("output/OpenSSL/decrypted_file", "wb");
    if (!f_dec) {
        /* Unable to open file for writing */
        fprintf(stderr, "ERROR: fopen error: %s\n", strerror(errno));
        return errno;
    };

    /* Decrypt*/
    file_encrypt_decrypt(params, f_input, f_dec);
    fclose(f_input);
    fclose(f_dec);

    free(params);

    return 0;
}