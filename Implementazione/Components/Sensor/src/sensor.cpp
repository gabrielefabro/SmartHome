#include "sensor.h"

// Costruttore della classe Sensor
Sensor::Sensor(int id, sensor_type state) : state(state), id(id), check(false) {}

// Funzione per ottenere lo stato attuale del sensore
sensor_type Sensor::getState() const
{
    return state;
}

// Funzione per ottenere l'ID del sensore
int Sensor::getId() const
{
    return id;
}

// Funzione per impostare lo stato di movimento del sensore
void Sensor::setCheck(bool value)
{
    check = value;
}

// Funzione per ottenere lo stato di movimento del sensore
bool Sensor::getCheck() const
{
    return check;
}

// Funzione per impostare manualmente lo stato del sensore
void Sensor::setState(sensor_type newState)
{
    state = newState;
}
