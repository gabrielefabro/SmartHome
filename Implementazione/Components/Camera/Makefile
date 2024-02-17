# Definizione delle directory
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := ./bin

# Lista dei file sorgente (.cpp) e degli header (.h)
SRCS := $(wildcard $(SRCDIR)/*.cpp)
HDRS := $(wildcard $(SRCDIR)/*.h)

# Genera la lista dei file oggetto (.o)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Nome del file eseguibile
EXEC := $(BINDIR)/main

# Compilatore e opzioni di compilazione
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

# Regola di compilazione generica
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regola per la creazione dell'eseguibile
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Target per la pulizia dei file intermedi e dell'eseguibile
.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

# Imposta il target predefinito come l'eseguibile
.DEFAULT_GOAL := $(EXEC)
