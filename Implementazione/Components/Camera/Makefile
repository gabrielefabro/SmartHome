# Definizione delle directory
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := ./bin

DIRSRCPSQ := ../../../con2db/src
DIROBJPSQ := ../../../con2db/obj

# Lista dei file sorgente (.cpp) e degli header (.h)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
HDRS := $(wildcard $(SRCDIR)/*.h)

SACS := $(wildcard $(DIRSRCPSQ)/*.cpp)
HARS := $(wildcard $(DIRSRCPSQ)/*.h)

# Genera la lista dei file oggetto (.o)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

OBJP := $(patsubst $(DIRSRCPSQ)/%.cpp,$(DIROBJPSQ)/%.o,$(SACS))

# Nome del file eseguibile
EXEC := $(BINDIR)/main

# Compilatore e opzioni di compilazione
CXX := g++
CFLAGS=-std=c++20 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
LIBDIR = -L/path/to/redis/lib
LIBS = -lhiredis -lpq -lm

# Regola di compilazione generica
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) -c $< -o $@ $(CFLAGS)

$(DIROBJPSQ)/%.o: %(DIRSRCPSQ)/%.cpp %(HARS)
	$(CXX) $(CFLAGS) -c $< -o $@

# Regola per la creazione dell'eseguibile
$(EXEC): $(OBJS) $(OBJP)
	$(CXX) $^ -o $@ $(CFLAGS) -L/path/to/redis/lib $(LIBS)

# Target per la pulizia dei file intermedi e dell'eseguibile
.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

# Imposta il target predefinito come l'eseguibile
.DEFAULT_GOAL := $(EXEC)