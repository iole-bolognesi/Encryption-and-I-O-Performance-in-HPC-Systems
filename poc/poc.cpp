/** 
* @file poc.cpp
* @brief This program is the proof of concept of our project. 
* 
* This implementation was adapted from:
* https://medium.com/@jmayuresh25/create-a-simple-file-encryption-system-in-c-e3726e0f265b
*
* This program encrypts and decrypts a file using Crypto++ 
* with AES-256-CBC and ADIOS2 for storage and retrieval. The read and write
* operations are performed serially but still using ADIOS 2.
*/
#include <files.h> 
#include "hex.h" 
#include <fstream>
#include <default.h> 
#include <adios2.h>
using namespace std;
using namespace CryptoPP;
using namespace adios2;

/**
 * @brief Writes data in parallel to an ADIOS2 file.
 * 
 * This function initializes an ADIOS2 IO object and writes the data passed  
 * as a aparameter to a file named "output/encrypted_adios.pb".
 * 
 * @param adios Reference to an ADIOS2 instance.
 * @param data Data to be written to the file.
 */
void writer(ADIOS &adios, const string &data)
{
    IO io = adios.DeclareIO("writer");
    Variable<string> varData = io.DefineVariable<string>("Data");
    Engine writer = io.Open("output/encrypted_adios.pb", Mode::Write);
    writer.BeginStep();
    writer.Put(varData, data);
    writer.EndStep();
    writer.Close();
}
/**
 * @brief Writes data in parallel to an ADIOS2 file.
 * 
 * This function initializes an ADIOS2 IO object, reads and returns the content 
 * the content of a file named "output/encrypted_adios.pb",
 * 
 * @param adios Reference to an ADIOS2 instance.
 * @return std::string Content read from the file
 */
string reader(ADIOS &adios)
{
    IO io = adios.DeclareIO("reader");
    Engine reader = io.Open("output/encrypted_adios.pb", Mode::Read);
    
    reader.BeginStep();
    Variable<string> varData = io.InquireVariable<string>("Data");
    string data;
    reader.Get(varData, data);
    reader.EndStep();
    reader.Close();
    return data;
}
/** 
 * Encrypts a file using AES-256-CBC with a password-based key and authentification.
 *
 * @param fileName The name of the file to encrypt.
 * @return std::string Encrypted file content  
 */
 string aesencrypt(char fileName[30]) {
    
    std::fstream fps;
    fps.open(fileName, std::fstream::in);
    if (!fps)
    {
        cout << "\nError!, Opening the Source File (to enctypt)!";
        return "";
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
    
    return encrypted;
};
/** 
 * Decrypts a string using AES-256-CBC with a password-based key and authentification.
 *
 * @param encrypted_data string to decrypt 
 * @return std::string Decrypted string
 */
 string aesdecrypt(string encrypted_data) {
    string password = "SecureComms123";
    string decrypted;
    StringSource ss1(encrypted_data, true,
        new HexDecoder(
            new DefaultDecryptorWithMAC(
                (byte*)&password[0], password.size(),
                new StringSink(decrypted)
            )
        )
    );
    return decrypted; 
};
int main(int argc, char *argv[]) {
    try
    {
        ADIOS adios;
        
        /* Encrypt */
        string encrypted_message = aesencrypt("input/signature");
        /* Store in parallel */
        writer(adios, encrypted_message);
        /* Read in parallel */
        const string message = reader(adios);
        /* Decrypt */
        cout<< aesdecrypt(message) <<endl;
    }
    catch (exception &e)
    {
        cout << "ERROR: ADIOS2 exception: " << e.what() << "\n";
    }
    return 0;
}
