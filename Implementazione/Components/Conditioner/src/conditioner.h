#ifndef CONDITIONER_H
#define CONDITIONER_H
#include <cstdlib>
#include "main.h"

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

    // Funzione per controllare lo stato delle luci
    conditioner_type getState() const;

    // Funzione per cambiare l'intesità delle luci
    void modifyTemperature(int Temperature);

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;
};

#endif // CONDITIONER_H