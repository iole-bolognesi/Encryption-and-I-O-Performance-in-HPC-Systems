CXX =icpc
CXXFLAGS= -Wall -O2 


# !!! IMPORTANT !!!
# Change these paths to point to your local installations of Crypto++ and ADIOS 2
CRYPTO_PATH := ./../cryptopp-master
ADIOS2_PATH := ./../adios2-install-bugfix

INCLUDES = \
    -I$(CRYPTO_PATH)\
    -I./include \
    -I./include/utils \
    -I./include/cipherWrappers \
    -I$(ADIOS2_PATH)/include \
    -I$(ADIOS2_PATH)/include/adios2/common

LIBDIRS := -L$(CRYPTO_PATH) -L$(ADIOS2_PATH)/lib64

LIBS = \
    -lcryptopp \
    -ladios2_cxx11 \
    -ladios2_cxx11_mpi

SRC = poc.cpp
TARGET_POC = ./bin/poc
TARGET = $(TARGET_POC)

all: crypto++

bin:
	mkdir -p bin

crypto++: bin $(TARGET)

$(TARGET): $(SRC)
			$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LIBDIRS) $(LIBS)

clean:
	rm -f $(TARGET) 

