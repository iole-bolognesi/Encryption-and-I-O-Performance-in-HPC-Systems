"""
AES File Encryption and Decryption

This program encrypts and decrypts a file using the cryptography package with AES-256-CBC. 

This implementation was taken and adapted from:
https://gist.github.com/brysontyrrell/7cebfb05105c25d00e84ed35bd821dfe

This program encrypts and decrypts files while ensuring that a secure random 
IV is used for each operation.

"""
import base64
import os
from cryptography.fernet import Fernet
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

def ensure_directory_exists(path):
    """
    Checks if a directory exists and creates it if it does not. 

    :param path: The path of the directory
    :return: None
    """
    if not os.path.exists(path):
        print(f"\nCreating directory: {path}")
        os.makedirs(path, exist_ok=True) 


class AESCipher(object):
    """
    This class provides variables and methods to implement AES encryption/decryption 
    using 256-bit keys in CBC mode.

    """

    block_size = int(algorithms.AES.block_size / 8)

    def __init__(self, key):
        """
        Initializes AES cipher with a 256-bit key.

        :param key: A 256-bit cryptographic key
        :raises ValueError: If the key size is not 256 bits 
        """
        if len(key) * 8 != 256:
            raise ValueError('Invalid key size (must be 256 bit)')
        self._key = key

    def _cipher(self, iv):
        """
        Creates and returns a new AES cipher context with CBC mode.

        :param iv: Initialization vector for CBC mode.
        :return: Cipher object
        """
        return Cipher(
            algorithms.AES(self._key),
            modes.CBC(iv),
            backend=default_backend()
        )

    def encrypt(self, raw):
        """
        Encrypts the given raw data using AES-256-CBC mode.

        :param raw: Data to be encrypted
        :return: Encrypted data
        """
        iv = os.urandom(AESCipher.block_size)
        encryptor = self._cipher(iv).encryptor()
        padded = self._pad(raw)
        cipher_text = encryptor.update(padded) + encryptor.finalize()
        return base64.b64encode(cipher_text + iv)

    def decrypt(self, encoded):
        """
        Decrypt the given encoded data using AES-256-CBC mode.

        :param encoded: Encrypted data.
        :return: Decrypted data.
        """
        raw = base64.b64decode(encoded)
        cipher_text = raw[:-AESCipher.block_size]
        iv = raw[-AESCipher.block_size:]
        decryptor = self._cipher(iv).decryptor()
        padded = decryptor.update(cipher_text) + decryptor.finalize()
        return self._unpad(padded)

    def _pad(self, raw):
        """
        Apply padding to the raw data ensuring it is a multiple of the block size.

        :param raw: Data to be padded.
        :return: Padded data.
        """
        ordinal = AESCipher.block_size - len(raw) % AESCipher.block_size
        return raw + bytes([ordinal] * ordinal)

    @staticmethod
    def _unpad(padded):
        """
        Remove PKCS7 padding from the padded data.

        :param padded: Padded data.
        :return: Unpadded original data.
        """
        return padded[:-padded[-1]]

def main():

    key = os.urandom(32)
    aes = AESCipher(key)

    ensure_directory_exists('./input/')
    with open('./input/signature', 'rb') as file:
        original = file.read()
        
    # encrypting the file
    encrypted = aes.encrypt(original)
    
    ensure_directory_exists('./output/cryptography/')
    with open('./output/cryptography/encrypted_file', 'wb') as encrypted_file:
        encrypted_file.write(encrypted)

    # decrypting the file
    decrypted = aes.decrypt(encrypted)
    
    with open('./output/cryptography/decrypted_file', 'wb') as decrypted_file:
        decrypted_file.write(decrypted)

if __name__ == "__main__":
    main()