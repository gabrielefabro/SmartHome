#ifndef CONDITIONER_H
#define CONDITIONER_H
#include <cstdlib>

typedef enum
{
    ON,
    OFF,
} conditioner_type;


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
    conditioner_type next(Conditioner conditioner);

    // Funzione per controllare lo stato delle luci
    conditioner_type getState() const;

    // Funzione per cambiare l'intesità delle luci
    void modifyTheLevel(int newLevel);

    // Funzione per ottenere l'ID della fotocamera
    int getId() const;
};

#endif // CONDITIONER_H