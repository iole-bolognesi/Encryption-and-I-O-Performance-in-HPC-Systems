#ifndef AES_HEADER 
#define AES_HEADER 

#define AES_256_KEY_SIZE 32 
#define AES_BLOCK_SIZE 16 
#define ERR_EVP_CIPHER_INIT -1
#define ERR_EVP_CIPHER_UPDATE -2
#define ERR_EVP_CIPHER_FINAL -3
#define ERR_EVP_CTX_NEW -4
#define BUFSIZE 1024

typedef struct _cipher_params_t{
    unsigned char *key;
    unsigned char *iv;
    unsigned int encrypt;
    const EVP_CIPHER *cipher_type;
}cipher_params_t;

void cleanup(cipher_params_t *params, FILE *ifp, FILE *ofp, int rc);
#endif