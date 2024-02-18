# Definizione delle directory
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := ./bin

DIRSRCPSQ := ../../con2db/src
DIROBJPSQ := ../../con2db/obj

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
CXXFLAGS := -Wall -Wextra -std=c++11

<<<<<<< HEAD
# Opzioni di linking per PostgreSQL e Redis
=======
>>>>>>> fb0c8a55095d71fc9ac088a9472b5b9a211a07d2
LIBS := -lpq -lhiredis

# Regola di compilazione generica
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIROBJPSQ)/%.o: %(DIRSRCPSQ)/%.cpp %(HARS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regola per la creazione dell'eseguibile
<<<<<<< HEAD
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)
=======
$(EXEC): $(OBJS) $(OBJP)
	$(CXX) $(CXXFLAGS) $^ -o $@
>>>>>>> fb0c8a55095d71fc9ac088a9472b5b9a211a07d2

# Target per la pulizia dei file intermedi e dell'eseguibile
.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

# Imposta il target predefinito come l'eseguibile
.DEFAULT_GOAL := $(EXEC)