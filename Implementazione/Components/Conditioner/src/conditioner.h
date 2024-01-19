#ifndef CONDITIONER_H
#define CONDITIONER_H
#include <cstdlib>
#include <iostream>


typedef enum
{
    ConditionerON,
    ConditionerOFF,
    change_temperature
} conditioner_type;



class Conditioner
{
private:
    conditioner_type state;
    int temperature;
    int id;

public:
    // Costruttore
    Conditioner(int id, int temperature, conditioner_type state);

    // Funzione per ottenere lo stato successivo
    conditioner_type next();

    // Funzione per controllare lo stato del conditioner
    conditioner_type getState() const;

    // Funzione per cambiare la temperatura del conditioner
    void modifyTemperature(int temperature);

    // Funzione per ottenere l'ID del conditioner
    int getId() const;

    int getTemperature() const;
};

#endif // CONDITIONER_H