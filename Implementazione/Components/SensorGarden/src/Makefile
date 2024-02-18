#IDIR=../hdr
IDIR=.
ODIR=../obj
BDIR=../bin
CC=g++
SRC_DB_DIR=../../../con2db/src
OBJ_DB_DIR=../../../con2db/obj

# use this when connecting to Postgresql (library lpq)
#CFLAGS=-std=c++11 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
CFLAGS=-std=c++20 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
LIBDIR = -L/path/to/redis/lib
LIBS = -lhiredis -lpq -lm
# use this when no connection to Postgresql (library lpq) is needed
#CFLAGS=-std=c++11 -I. -I$(IDIR) -lm 
DEPS = $(wildcard $(IDIR)/*.h)
DEPS7 = $(wildcard $(SRC_DB_DIR)/*.h)


SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

SRC_DB = $(wildcard $(SRC_DB_DIR)/*.cpp)
OBJ_DB = $(patsubst $(SRC_DB_DIR)/%.cpp, $(OBJ_DB_DIR)/%.o, $(SRC_DB))



all: $(BDIR)/main

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DB_DIR)/%.o: $(SRC_DB_DIR)/%.cpp $(DEPS7)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ) $(OBJ_DB) $(DEPS) $(DEPS7)
	$(CC) -o $@ $(OBJ) $(OBJ_DB) $(CFLAGS) -L/path/to/redis/lib $(LIBS)