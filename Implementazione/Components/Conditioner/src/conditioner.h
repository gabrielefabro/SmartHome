#ifndef CONDITIONER_H
#define CONDITIONER_H

#include <cstdlib>
#include <iostream>
#include "pgsql.h"
#include <chrono>
void timeFlies(char *buf);

// Enumerazione che rappresenta i possibili stati del condizionatore.
typedef enum
{
    ConditionerON,
    ConditionerOFF,
    change_temperature
} conditioner_type;

// Dichiarazione della classe Conditioner.
class Conditioner
{
private:
    // Variabile che rappresenta l'identificatore del condizionatore.
    int id;

    // Variabile che rappresenta la temperatura del condizionatore.
    int temperature;

    // Variabile di stato del condizionatore.
    conditioner_type state;

    

public:
    // Costruttore della classe Conditioner.
    Conditioner(int id, int temperature, conditioner_type state);

    // Funzione per ottenere lo stato corrente del condizionatore.
    conditioner_type getState() const;

    // Funzione per modificare manualmente la temperatura del condizionatore.
    void modifyTemperature(int temperature);

    // Funzione per ottenere l'ID del condizionatore.
    int getId() const;

    // Funzione per ottenere la temperatura corrente del condizionatore.
    int getTemperature() const;

    // Funzione per impostare manualmente lo stato del condizionatore.
    void setState(conditioner_type newState);
};

Conditioner initConditioner();
void log2conditionerdb(Con2DB db1, int id, int pid, conditioner_type state, int temperature, int64_t tempo_trascorso);
void int2stateConditioner(char *cstate, conditioner_type state);

#endif
