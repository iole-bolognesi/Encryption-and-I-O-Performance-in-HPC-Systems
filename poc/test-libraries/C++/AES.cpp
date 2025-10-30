/** 
* @file AES.cpp
* @brief This program encrypts and decrypts a file using crypto++ with AES-256-CBC.

This implementation was taken and adapted from:
https://medium.com/@jmayuresh25/create-a-simple-file-encryption-system-in-c-e3726e0f265b

This program encrypts a file in in hex format and decrypts it back in its original 
form with password-based key derivation (instead of a random key generation) and authentification. 
*/

#include <sstream>  
#include <files.h> 
#include "hex.h" 
#include <fstream>
#include <default.h> 
#include <sys/stat.h> 

using namespace std;
using namespace CryptoPP;

/** 
 * Checks if a directory exists and creates it if it does not. 
 *
 * @param path Reference to directory path.
 */
void ensureDirectoryExists(const string &path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        cout << "\nCreating directory: " << path << endl;
        system(("mkdir -p " + path).c_str());  // Create the directory
    }
}

/** 
 * Encrypts a file using AES-256-CBC with a password-based key and authentification.
 *
 * @param fileName The name of the file to encrypt.
 * @return 0 on success, 1 if the input file cannot be opened.
 */
int aesencrypt(char fileName[30]) {
    char ch;
    fstream fps, fpt;

    fps.open(fileName, fstream::in);
    if (!fps)
    {
        cout << "\nError!, Opening the Source File (to encrypt)!";
        return 1;
    }

    string password;
    string encrypted;
    password = "SecureComms123";

    FileSource fs1(fileName, true,
        new DefaultEncryptorWithMAC(
            (byte*)&password[0], password.size(),
              new HexEncoder(
                   new StringSink(encrypted)
                )
        )
    );
    
    ensureDirectoryExists("./output/crypto++/");
    fpt.open("output/crypto++/encrypted_file",  fstream::out);
    fpt << encrypted;
    return 0;

};

/** 
 * Decrypts a file using AES-256-CBC with a password-based key and authentification.
 *
 * @param fileName The name of the file to decrypt.
 * @return 0 on success, 1 if the input file cannot be opened.
 */

int aesdecrypt(char fileName[30]) {
    char ch;
    fstream fps, fpt;
    fps.open(fileName, fstream::in);

    if (!fps)
    {
        cout << "\nError!, Opening the Source File (to decrypt)!";
        return 1;
    }

    string password = "SecureComms123";
    string encrypted, decrypted;

    stringstream buffer;
    buffer << fps.rdbuf();  
    encrypted = buffer.str(); 


    StringSource ss1(encrypted, true,
        new HexDecoder(
            new DefaultDecryptorWithMAC(
                (byte*)&password[0], password.size(),
                new StringSink(decrypted)
            )
        )
    );

    fpt.open("output/crypto++/decrypted_file",  fstream::out);
    fpt << decrypted;

    return 0; 
};

int main(int argc, char *argv[]) {

    /* Encrypt */
    ensureDirectoryExists("./input/");
    aesencrypt("./input/signature");

    /* Decrypt */
    ensureDirectoryExists("./output/crypto++/");
    aesdecrypt("./output/crypto++/encrypted_file");

    return 0;
}

