#include "sensor.h"

// Costruttore della classe Sensor
Sensor::Sensor(int id, sensor_type state) : state(state), id(id), movement(false) {}

// Funzione per ottenere lo stato successivo del sensore in modo casuale
sensor_type Sensor::next()
{
    state = static_cast<sensor_type>(rand() % 3);
    return state;
}

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
void Sensor::setMovement(bool value)
{
    movement = value;
}

// Funzione per ottenere lo stato di movimento del sensore
bool Sensor::getMovement() const
{
    return movement;
}

// Funzione per impostare manualmente lo stato del sensore
void Sensor::setState(sensor_type newState)
{
    state = newState;
}
