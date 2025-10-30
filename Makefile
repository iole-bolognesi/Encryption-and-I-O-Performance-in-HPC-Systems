# -------- compilation flags ----------------------------------------------

CXX_MPI  = mpicxx
CXX  = icpc
CXXFLAGS = -Wall -O2 -std=c++17
ADIOS2_MPI_FLAG = -DADIOS2_USE_MPI

# -------- linker flags --------------------------------------------------

# !!! IMPORTANT !!!
# Change these paths to point to your local installations of Crypto++ and ADIOS 2
CRYPTO_PATH := ./cryptopp-master
ADIOS2_PATH := ./adios2-install-bugfix

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
# ------------------------------------------------------------------------

PAR_TARGET = bin/parallel 
SER_TARGET = bin/serial 
TEST_TARGET = bin/test 

TARGET = $(PAR_TARGET) $(SER_TARGET) $(TEST_TARGET)

SRC = $(wildcard src/*.cpp) \
      $(wildcard src/utils/*.cpp) \
      $(wildcard src/cipherWrappers/*.cpp)

PAR_MAIN = src/parallelPipeline.cpp
SER_MAIN = src/serialPipeline.cpp
TEST_MAIN = src/testing.cpp
COMMON_SRC = $(filter-out $(PAR_MAIN) $(SER_MAIN) $(TEST_MAIN), $(SRC))

PAR_SRC = $(PAR_MAIN) $(COMMON_SRC)
SER_SRC = $(SER_MAIN) $(COMMON_SRC)
TEST_SRC = $(TEST_MAIN) 
# ------------------------------------------------------------------------

all: parallel serial test 

bin:
	mkdir -p bin

parallel: bin $(PAR_TARGET)
$(PAR_TARGET): $(PAR_SRC)
	$(CXX_MPI) $(CXXFLAGS) $(ADIOS2_MPI_FLAG) -o $@ $^ $(INCLUDES) $(LIBDIRS) $(LIBS)

serial: bin $(SER_TARGET)
$(SER_TARGET): $(SER_SRC)
	$(CXX_MPI) $(CXXFLAGS) $(ADIOS2_MPI_FLAG) -o $@ $^ $(INCLUDES) $(LIBDIRS) $(LIBS)

test: bin $(TEST_TARGET)
$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean: clean-all

clean-all:
	rm -f $(TARGET)

clean-parallel:
	rm -f $(PAR_TARGET)

clean-serial:
	rm -f $(SER_TARGET)

clean-test:
	rm -f $(TEST_TARGET)


.PHONY: clean clean-all clean-parallel clean-serial clean-test
    
