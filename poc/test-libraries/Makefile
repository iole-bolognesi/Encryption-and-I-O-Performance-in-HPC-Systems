CC  = icc
CXX = icpc
CFLAGS    = -Wall -O2
CXXFLAGS  = -Wall -O2

# !!! IMPORTANT !!!
# Change these paths to point to your local installation of Crypto++ 
CRYPTO_PATH       = ./../../cryptopp-master

OPENSSL_INCLUDES  = -I./C
OPENSSL_LIBS      = -lcrypto -lssl

CRYPTO_INCLUDES   = -I$(CRYPTO_PATH)
CRYPTO_LIBDIRS    = -L$(CRYPTO_PATH)
CRYPTO_LIBS       = -lcryptopp

SRC_C    = ./C/AES.c
SRC_CPP  = ./C++/AES.cpp
TARGET_C   = bin/aes_openssl
TARGET_CPP = bin/aes_cryptopp

.PHONY: all openssl crypto++ clean bin

all: openssl crypto++

bin:
	mkdir -p bin

openssl: bin $(TARGET_C)
$(TARGET_C): $(SRC_C)
	$(CC) $(CFLAGS) -o $@ $^ $(OPENSSL_INCLUDES) $(OPENSSL_LIBS)

crypto++: bin $(TARGET_CPP)
$(TARGET_CPP): $(SRC_CPP)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CRYPTO_INCLUDES) $(CRYPTO_LIBDIRS) $(CRYPTO_LIBS)

clean:
	rm -f $(TARGET_C) $(TARGET_CPP)
