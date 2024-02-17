#include "conditioner.h"

// Implementazione del costruttore della classe Conditioner.
Conditioner::Conditioner(int id, int temperature, conditioner_type state) : id(id), temperature(temperature), state(state) {}

// Funzione per ottenere lo stato corrente del condizionatore.
conditioner_type Conditioner::getState() const
{
    return state;
}

// Funzione per modificare manualmente la temperatura del condizionatore.
void Conditioner::modifyTemperature(int newTemperature)
{
    temperature = newTemperature;
}

// Funzione per ottenere l'ID del condizionatore.
int Conditioner::getId() const
{
    return id;
}

// Funzione per ottenere la temperatura corrente del condizionatore.
int Conditioner::getTemperature() const
{
    return temperature;
}

// Funzione per impostare manualmente lo stato del condizionatore.
void Conditioner::setState(conditioner_type newState)
{
    state = newState;
}
