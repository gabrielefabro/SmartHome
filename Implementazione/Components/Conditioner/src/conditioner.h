#ifndef CONDITIONER_H
#define CONDITIONER_H
#include <cstdlib>

class Conditioner
{
private:
    conditioner_type state;
    int level;
    int id;

public:
    // Costruttore
    Conditioner(int id, int level, conditioner_type state);

    // Funzione per ottenere lo stato successivo
    conditioner_type next();

    // Funzione per controllare lo stato del conditioner
    conditioner_type getState() const;

    // Funzione per cambiare la temperatura del conditioner
    void modifyTemperature(int Temperature);

    // Funzione per ottenere l'ID del conditioner
    int getId() const;
};

#endif // CONDITIONER_H